#pragma once

#include "Resource.h"
#include <vector>
#include <map>

namespace Ship
{
	struct AdsrEnvelope
	{
		int16_t delay;
		int16_t arg;
	};

	struct AdpcmBook
	{
		/* 0x00 */ int32_t order;
		/* 0x04 */ int32_t npredictors;
		/* 0x08 */ std::vector<int16_t> books;  // size 8 * order * npredictors. 8-byte aligned
	};

	struct AdpcmLoop
	{
		/* 0x00 */ uint32_t start;
		/* 0x04 */ uint32_t end;
		/* 0x08 */ uint32_t count;
		///* 0x10 */ int16_t state[16];  // only exists if count != 0. 8-byte aligned
		/* 0x10 */ std::vector<int16_t> states;
	};

	struct SoundFontEntry
	{
		//SampleEntry* sampleEntry = nullptr;
		uint32_t sampleOffset;
		float tuning;
	};

	struct DrumEntry
	{
		uint8_t releaseRate;
		uint8_t pan;
		uint8_t loaded;
		uint32_t offset;
		float tuning;
		std::vector<AdsrEnvelope*> env;
		//SampleEntry* sample = nullptr;
	};

	struct InstrumentEntry
	{
		bool isValidEntry;
		uint8_t loaded;
		uint8_t normalRangeLo;
		uint8_t normalRangeHi;
		uint8_t releaseRate;
		std::vector<AdsrEnvelope*> env;
		SoundFontEntry* lowNotesSound = nullptr;
		SoundFontEntry* normalNotesSound = nullptr;
		SoundFontEntry* highNotesSound = nullptr;
	};

	class AudioSoundFontV1 : public ResourceFile
	{
	public:
		void ParseFileBinary(BinaryReader* reader, Resource* res) override;
		static std::vector<AdsrEnvelope*> ReadEnvelopeData(BinaryReader* reader);
	};

	class AudioSampleV1 : public ResourceFile
	{
	public:
		void ParseFileBinary(BinaryReader* reader, Resource* res) override;
	};
	
	class AudioV1 : public ResourceFile
	{
	public:
		void ParseFileBinary(BinaryReader* reader, Resource* res) override;
	};

	struct AudioSoundFont : public Resource
	{
	public:
		uint32_t ptr;
		uint32_t size;
		uint8_t medium;
		uint8_t cachePolicy;
		uint16_t data1;
		uint16_t data2;
		uint16_t data3;

		std::vector<DrumEntry> drums;
		std::vector<SoundFontEntry*> soundEffects;
		std::vector<InstrumentEntry> instruments;
	};

	class AudioSample : public Resource
	{
	public:
		uint8_t codec;
		uint8_t medium;
		uint8_t unk_bit26;
		uint8_t unk_bit25;

		std::vector<uint8_t> data;
		AdpcmLoop loop;
		AdpcmBook book;
	};

	class Audio : public Resource
	{
	public:
		//std::vector<AudioTableEntry> soundFontTable;
		//std::vector<AudioTableEntry> sequenceTable;
		//std::vector<AudioTableEntry> sampleBankTable;
		//std::vector<char*> sequences;
		//std::vector<SampleEntry*> samples;

	};
}