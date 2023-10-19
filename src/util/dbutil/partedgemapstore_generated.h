// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_PARTEDGEMAPSTORE_JASMINEGRAPH_PARTEDGEMAPSTORE_H_
#define FLATBUFFERS_GENERATED_PARTEDGEMAPSTORE_JASMINEGRAPH_PARTEDGEMAPSTORE_H_

#include "flatbuffers/flatbuffers.h"

namespace JasmineGraph {
namespace PartEdgeMapStore {

struct PartEdgeMapStore;

struct PartEdgeMapStoreEntry;

struct PartEdgeMapStore FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
    enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE { VT_ENTRIES = 4 };
    const flatbuffers::Vector<flatbuffers::Offset<PartEdgeMapStoreEntry>> *entries() const {
        return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<PartEdgeMapStoreEntry>> *>(VT_ENTRIES);
    }
    bool Verify(flatbuffers::Verifier &verifier) const {
        return VerifyTableStart(verifier) && VerifyOffset(verifier, VT_ENTRIES) && verifier.VerifyVector(entries()) &&
               verifier.VerifyVectorOfTables(entries()) && verifier.EndTable();
    }
};

struct PartEdgeMapStoreBuilder {
    flatbuffers::FlatBufferBuilder &fbb_;
    flatbuffers::uoffset_t start_;
    void add_entries(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<PartEdgeMapStoreEntry>>> entries) {
        fbb_.AddOffset(PartEdgeMapStore::VT_ENTRIES, entries);
    }
    explicit PartEdgeMapStoreBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
    PartEdgeMapStoreBuilder &operator=(const PartEdgeMapStoreBuilder &);
    flatbuffers::Offset<PartEdgeMapStore> Finish() {
        const auto end = fbb_.EndTable(start_);
        auto o = flatbuffers::Offset<PartEdgeMapStore>(end);
        return o;
    }
};

inline flatbuffers::Offset<PartEdgeMapStore> CreatePartEdgeMapStore(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<PartEdgeMapStoreEntry>>> entries = 0) {
    PartEdgeMapStoreBuilder builder_(_fbb);
    builder_.add_entries(entries);
    return builder_.Finish();
}

inline flatbuffers::Offset<PartEdgeMapStore> CreatePartEdgeMapStoreDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<PartEdgeMapStoreEntry>> *entries = nullptr) {
    auto entries__ = entries ? _fbb.CreateVector<flatbuffers::Offset<PartEdgeMapStoreEntry>>(*entries) : 0;
    return JasmineGraph::PartEdgeMapStore::CreatePartEdgeMapStore(_fbb, entries__);
}

struct PartEdgeMapStoreEntry FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
    enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE { VT_KEY = 4, VT_VALUE = 6 };
    int32_t key() const { return GetField<int32_t>(VT_KEY, 0); }
    bool KeyCompareLessThan(const PartEdgeMapStoreEntry *o) const { return key() < o->key(); }
    int KeyCompareWithValue(int32_t val) const { return static_cast<int>(key() > val) - static_cast<int>(key() < val); }
    const flatbuffers::Vector<int32_t> *value() const {
        return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_VALUE);
    }
    bool Verify(flatbuffers::Verifier &verifier) const {
        return VerifyTableStart(verifier) && VerifyField<int32_t>(verifier, VT_KEY) &&
               VerifyOffset(verifier, VT_VALUE) && verifier.VerifyVector(value()) && verifier.EndTable();
    }
};

struct PartEdgeMapStoreEntryBuilder {
    flatbuffers::FlatBufferBuilder &fbb_;
    flatbuffers::uoffset_t start_;
    void add_key(int32_t key) { fbb_.AddElement<int32_t>(PartEdgeMapStoreEntry::VT_KEY, key, 0); }
    void add_value(flatbuffers::Offset<flatbuffers::Vector<int32_t>> value) {
        fbb_.AddOffset(PartEdgeMapStoreEntry::VT_VALUE, value);
    }
    explicit PartEdgeMapStoreEntryBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) {
        start_ = fbb_.StartTable();
    }
    PartEdgeMapStoreEntryBuilder &operator=(const PartEdgeMapStoreEntryBuilder &);
    flatbuffers::Offset<PartEdgeMapStoreEntry> Finish() {
        const auto end = fbb_.EndTable(start_);
        auto o = flatbuffers::Offset<PartEdgeMapStoreEntry>(end);
        return o;
    }
};

inline flatbuffers::Offset<PartEdgeMapStoreEntry> CreatePartEdgeMapStoreEntry(
    flatbuffers::FlatBufferBuilder &_fbb, int32_t key = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> value = 0) {
    PartEdgeMapStoreEntryBuilder builder_(_fbb);
    builder_.add_value(value);
    builder_.add_key(key);
    return builder_.Finish();
}

inline flatbuffers::Offset<PartEdgeMapStoreEntry> CreatePartEdgeMapStoreEntryDirect(
    flatbuffers::FlatBufferBuilder &_fbb, int32_t key = 0, const std::vector<int32_t> *value = nullptr) {
    auto value__ = value ? _fbb.CreateVector<int32_t>(*value) : 0;
    return JasmineGraph::PartEdgeMapStore::CreatePartEdgeMapStoreEntry(_fbb, key, value__);
}

inline const JasmineGraph::PartEdgeMapStore::PartEdgeMapStore *GetPartEdgeMapStore(const void *buf) {
    return flatbuffers::GetRoot<JasmineGraph::PartEdgeMapStore::PartEdgeMapStore>(buf);
}

inline const JasmineGraph::PartEdgeMapStore::PartEdgeMapStore *GetSizePrefixedPartEdgeMapStore(const void *buf) {
    return flatbuffers::GetSizePrefixedRoot<JasmineGraph::PartEdgeMapStore::PartEdgeMapStore>(buf);
}

inline bool VerifyPartEdgeMapStoreBuffer(flatbuffers::Verifier &verifier) {
    return verifier.VerifyBuffer<JasmineGraph::PartEdgeMapStore::PartEdgeMapStore>(nullptr);
}

inline bool VerifySizePrefixedPartEdgeMapStoreBuffer(flatbuffers::Verifier &verifier) {
    return verifier.VerifySizePrefixedBuffer<JasmineGraph::PartEdgeMapStore::PartEdgeMapStore>(nullptr);
}

inline void FinishPartEdgeMapStoreBuffer(flatbuffers::FlatBufferBuilder &fbb,
                                         flatbuffers::Offset<JasmineGraph::PartEdgeMapStore::PartEdgeMapStore> root) {
    fbb.Finish(root);
}

inline void FinishSizePrefixedPartEdgeMapStoreBuffer(
    flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<JasmineGraph::PartEdgeMapStore::PartEdgeMapStore> root) {
    fbb.FinishSizePrefixed(root);
}

}  // namespace PartEdgeMapStore
}  // namespace JasmineGraph

#endif  // FLATBUFFERS_GENERATED_PARTEDGEMAPSTORE_JASMINEGRAPH_PARTEDGEMAPSTORE_H_
