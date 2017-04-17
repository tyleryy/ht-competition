#include "StreamParser.h"
#include "stdio.h"
#include "datalink/datalink.h"

//#define SPDEBUG

#ifdef SPDEBUG
#define sp_debug(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define sp_debug(fmt, ...)
#endif

/* Declare private function prototypes */
u8 parsePacketPayload(ThinkGearStreamParser *parser);

/**
 * @return 1 if @c parserType is invalid.
 * @return 0 on success.
 */

u8 THINKGEAR_initParser(ThinkGearStreamParser *parser, unsigned char parserType)
{

	/* Initialize the parser's state based on the parser type */
	switch (parserType)
	{
	case (PARSER_TYPE_PACKETS):
		parser->state = PARSER_STATE_SYNC;
		break;
	case (PARSER_TYPE_2BYTERAW):
		parser->state = PARSER_STATE_WAIT_HIGH;
		break;
	default:
		return (1);
	}

	/* Save parser type */
	parser->type = parserType;

	return (0);
}

/**
 *
 * @return 1 if @c parser is NULL.
 * @return 2 if a complete Packet was received, but the checksum failed.
 * @return 3 if an invalid Packet with PLENGTH > 170 was detected.
 * @return 4 if an invalid Packet with PLENGTH == 170 was detected.
 * @return 5 if the @c parser is somehow in an unrecognized state.
 * @return 6 if the @c byte did not yet complete a Packet.
 * @return 0 if a Packet was received and parsed successfully.
 *
 */

u8 THINKGEAR_parseByte(ThinkGearStreamParser *parser, unsigned char byte)
{

	u8 returnValue = 6;

	if (!parser)
	{
		return (1);

	}
	/* Pick handling according to current state... */
	switch (parser->state)
	{

	/* Waiting for SyncByte */
	case (PARSER_STATE_SYNC):
		if (byte == PARSER_SYNC_BYTE)
		{
			parser->state = PARSER_STATE_SYNC_CHECK;

		}
		break;

		/* Waiting for second SyncByte */
	case (PARSER_STATE_SYNC_CHECK):
		if (byte == PARSER_SYNC_BYTE)
		{
			parser->state = PARSER_STATE_PAYLOAD_LENGTH;
		}
		else
		{
			parser->state = PARSER_STATE_SYNC;
		}
		break;

		/* Waiting for Data[] length */
	case (PARSER_STATE_PAYLOAD_LENGTH):
		parser->payloadLength = byte;
		if (parser->payloadLength > 170)
		{
			parser->state = PARSER_STATE_SYNC;
			returnValue = 3;
		}
		else if (parser->payloadLength == 170)
		{
			parser->state = PARSER_STATE_SYNC;
			returnValue = 4;
		}
		else
		{
			parser->payloadBytesReceived = 0;
			parser->payloadSum = 0;
			parser->state = PARSER_STATE_PAYLOAD;
		}
		break;

		/* Waiting for Payload[] bytes */
	case (PARSER_STATE_PAYLOAD):
		parser->payload[parser->payloadBytesReceived++] = byte;
		parser->payloadSum = (unsigned char) (parser->payloadSum + byte);
		if (parser->payloadBytesReceived >= parser->payloadLength)
		{
			parser->state = PARSER_STATE_CHKSUM;
		}
		break;

		/* Waiting for CKSUM byte */
	case (PARSER_STATE_CHKSUM):
		parser->chksum = byte;
		parser->state = PARSER_STATE_SYNC;
		if (parser->chksum != ((~parser->payloadSum) & 0xFF))
		{
			parser->state = PARSER_STATE_SYNC;
			returnValue = 2;
		}
		else
		{
			returnValue = 0;
			parsePacketPayload(parser);
		}
		break;

		/* unrecognized state */
	default:
		parser->state = PARSER_STATE_SYNC;
		returnValue = 5;
		break;

	}

	/* Save current byte */
	parser->lastByte = byte;

	return (returnValue);
}

/**
 * Parses each row of data from the @c packet's Data[] block,
 * updating the fields of @c data as appropriate.
 */
u8 parsePacketPayload(ThinkGearStreamParser *parser)
{
	u8 returnValue = 0;

	unsigned char i = 0;
	unsigned char extendedCodeLevel = 0;
	unsigned char code = 0;
	unsigned char numBytes = 0;

	/* Parse all bytes from the payload[] */
	while (i < parser->payloadLength)
	{

		/* Parse possible EXtended CODE bytes */
		while (parser->payload[i] == PARSER_EXCODE_BYTE)
		{
			extendedCodeLevel++;
			i++;
		}

		/* Parse CODE */
		code = parser->payload[i++];

		/* Parse value length */
		if (code >= 0x80)
			numBytes = parser->payload[i++];
		else
			numBytes = 1;

		/* Call the callback function to handle the DataRow value */

		switch (code)
		{
		case PARSER_CODE_POOR_QUALITY:
			parser->signal = parser->payload[i];
			parser->signalrdy = 1;
			sp_debug("signal<%d>", parser->signal);
			break;

		case PARSER_CODE_ATTENTION:
			parser->attention = parser->payload[i];
			parser->attentionrdy = 1;
			sp_debug("attention:<%d>\n", parser->attention);
			break;
		case PARSER_CODE_MEDITATION:
			parser->meditation = parser->payload[i];
			sp_debug("meditation:<%d>\n", parser->meditation);
			break;
		case 0x16:
			parser->blink_strength = parser->payload[i];
			sp_debug("blink_strength:<%d>\n", parser->blink_strength);
			break;
		case PARSER_CODE_ASIC_EEG_POWER_INT:
			//while(m<num)  EEG_power[m]=payload[n++];
			break;
		case PARSER_CODE_RAW_SIGNAL:
			//while(m<num) raw_wave_value[m]=payload[n++];
			//sp_debug("they are values of raw signal.\n");

			break;
		default:
			returnValue = 1;

			break;
		}

		i = (unsigned char) (i + numBytes);
	}

	return (returnValue);
}

