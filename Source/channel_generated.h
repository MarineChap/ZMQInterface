// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CHANNEL_H_
#define FLATBUFFERS_GENERATED_CHANNEL_H_

#include "flatbuffers/flatbuffers.h"

struct ContinuousData;
struct ContinuousDataBuilder;

struct ContinuousData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ContinuousDataBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SAMPLES = 4,
    VT_CHANNEL_NBR = 6,
    VT_NBR_SAMPLES = 8,
    VT_TIMESTAMPS = 10,
    VT_MESSAGE_NO = 12,
    VT_SAMPLE_RATE = 14
  };
  const flatbuffers::Vector<float> *samples() const {
    return GetPointer<const flatbuffers::Vector<float> *>(VT_SAMPLES);
  }
  int32_t channel_nbr() const {
    return GetField<int32_t>(VT_CHANNEL_NBR, 0);
  }
  int32_t nbr_samples() const {
    return GetField<int32_t>(VT_NBR_SAMPLES, 0);
  }
  int64_t timestamps() const {
    return GetField<int64_t>(VT_TIMESTAMPS, 0);
  }
  int64_t message_no() const {
    return GetField<int64_t>(VT_MESSAGE_NO, 0);
  }
  int32_t sample_rate() const {
    return GetField<int32_t>(VT_SAMPLE_RATE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_SAMPLES) &&
           verifier.VerifyVector(samples()) &&
           VerifyField<int32_t>(verifier, VT_CHANNEL_NBR) &&
           VerifyField<int32_t>(verifier, VT_NBR_SAMPLES) &&
           VerifyField<int64_t>(verifier, VT_TIMESTAMPS) &&
           VerifyField<int64_t>(verifier, VT_MESSAGE_NO) &&
           VerifyField<int32_t>(verifier, VT_SAMPLE_RATE) &&
           verifier.EndTable();
  }
};

struct ContinuousDataBuilder {
  typedef ContinuousData Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_samples(flatbuffers::Offset<flatbuffers::Vector<float>> samples) {
    fbb_.AddOffset(ContinuousData::VT_SAMPLES, samples);
  }
  void add_channel_nbr(int32_t channel_nbr) {
    fbb_.AddElement<int32_t>(ContinuousData::VT_CHANNEL_NBR, channel_nbr, 0);
  }
  void add_nbr_samples(int32_t nbr_samples) {
    fbb_.AddElement<int32_t>(ContinuousData::VT_NBR_SAMPLES, nbr_samples, 0);
  }
  void add_timestamps(int64_t timestamps) {
    fbb_.AddElement<int64_t>(ContinuousData::VT_TIMESTAMPS, timestamps, 0);
  }
  void add_message_no(int64_t message_no) {
    fbb_.AddElement<int64_t>(ContinuousData::VT_MESSAGE_NO, message_no, 0);
  }
  void add_sample_rate(int32_t sample_rate) {
    fbb_.AddElement<int32_t>(ContinuousData::VT_SAMPLE_RATE, sample_rate, 0);
  }
  explicit ContinuousDataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ContinuousData> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ContinuousData>(end);
    return o;
  }
};

inline flatbuffers::Offset<ContinuousData> CreateContinuousData(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<float>> samples = 0,
    int32_t channel_nbr = 0,
    int32_t nbr_samples = 0,
    int64_t timestamps = 0,
    int64_t message_no = 0,
    int32_t sample_rate = 0) {
  ContinuousDataBuilder builder_(_fbb);
  builder_.add_message_no(message_no);
  builder_.add_timestamps(timestamps);
  builder_.add_sample_rate(sample_rate);
  builder_.add_nbr_samples(nbr_samples);
  builder_.add_channel_nbr(channel_nbr);
  builder_.add_samples(samples);
  return builder_.Finish();
}

inline flatbuffers::Offset<ContinuousData> CreateContinuousDataDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<float> *samples = nullptr,
    int32_t channel_nbr = 0,
    int32_t nbr_samples = 0,
    int64_t timestamps = 0,
    int64_t message_no = 0,
    int32_t sample_rate = 0) {
  auto samples__ = samples ? _fbb.CreateVector<float>(*samples) : 0;
  return CreateContinuousData(
      _fbb,
      samples__,
      channel_nbr,
      nbr_samples,
      timestamps,
      message_no,
      sample_rate);
}

inline const ContinuousData *GetContinuousData(const void *buf) {
  return flatbuffers::GetRoot<ContinuousData>(buf);
}

inline const ContinuousData *GetSizePrefixedContinuousData(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<ContinuousData>(buf);
}

inline bool VerifyContinuousDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<ContinuousData>(nullptr);
}

inline bool VerifySizePrefixedContinuousDataBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<ContinuousData>(nullptr);
}

inline void FinishContinuousDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<ContinuousData> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedContinuousDataBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<ContinuousData> root) {
  fbb.FinishSizePrefixed(root);
}

#endif  // FLATBUFFERS_GENERATED_CHANNEL_H_
