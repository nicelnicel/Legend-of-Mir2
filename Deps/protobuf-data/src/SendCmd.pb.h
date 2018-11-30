// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SendCmd.proto

#ifndef PROTOBUF_INCLUDED_SendCmd_2eproto
#define PROTOBUF_INCLUDED_SendCmd_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_SendCmd_2eproto 

namespace protobuf_SendCmd_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_SendCmd_2eproto
namespace SocketData {
class CmdRequest;
class CmdRequestDefaultTypeInternal;
extern CmdRequestDefaultTypeInternal _CmdRequest_default_instance_;
class CmdResponse;
class CmdResponseDefaultTypeInternal;
extern CmdResponseDefaultTypeInternal _CmdResponse_default_instance_;
}  // namespace SocketData
namespace google {
namespace protobuf {
template<> ::SocketData::CmdRequest* Arena::CreateMaybeMessage<::SocketData::CmdRequest>(Arena*);
template<> ::SocketData::CmdResponse* Arena::CreateMaybeMessage<::SocketData::CmdResponse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace SocketData {

// ===================================================================

class CmdRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:SocketData.CmdRequest) */ {
 public:
  CmdRequest();
  virtual ~CmdRequest();

  CmdRequest(const CmdRequest& from);

  inline CmdRequest& operator=(const CmdRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CmdRequest(CmdRequest&& from) noexcept
    : CmdRequest() {
    *this = ::std::move(from);
  }

  inline CmdRequest& operator=(CmdRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CmdRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CmdRequest* internal_default_instance() {
    return reinterpret_cast<const CmdRequest*>(
               &_CmdRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(CmdRequest* other);
  friend void swap(CmdRequest& a, CmdRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CmdRequest* New() const final {
    return CreateMaybeMessage<CmdRequest>(NULL);
  }

  CmdRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<CmdRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const CmdRequest& from);
  void MergeFrom(const CmdRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CmdRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes Content = 2;
  void clear_content();
  static const int kContentFieldNumber = 2;
  const ::std::string& content() const;
  void set_content(const ::std::string& value);
  #if LANG_CXX11
  void set_content(::std::string&& value);
  #endif
  void set_content(const char* value);
  void set_content(const void* value, size_t size);
  ::std::string* mutable_content();
  ::std::string* release_content();
  void set_allocated_content(::std::string* content);

  // uint32 Timer = 1;
  void clear_timer();
  static const int kTimerFieldNumber = 1;
  ::google::protobuf::uint32 timer() const;
  void set_timer(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:SocketData.CmdRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr content_;
  ::google::protobuf::uint32 timer_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_SendCmd_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class CmdResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:SocketData.CmdResponse) */ {
 public:
  CmdResponse();
  virtual ~CmdResponse();

  CmdResponse(const CmdResponse& from);

  inline CmdResponse& operator=(const CmdResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CmdResponse(CmdResponse&& from) noexcept
    : CmdResponse() {
    *this = ::std::move(from);
  }

  inline CmdResponse& operator=(CmdResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CmdResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CmdResponse* internal_default_instance() {
    return reinterpret_cast<const CmdResponse*>(
               &_CmdResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(CmdResponse* other);
  friend void swap(CmdResponse& a, CmdResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CmdResponse* New() const final {
    return CreateMaybeMessage<CmdResponse>(NULL);
  }

  CmdResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<CmdResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const CmdResponse& from);
  void MergeFrom(const CmdResponse& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CmdResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bool Status = 1;
  void clear_status();
  static const int kStatusFieldNumber = 1;
  bool status() const;
  void set_status(bool value);

  // @@protoc_insertion_point(class_scope:SocketData.CmdResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool status_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_SendCmd_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CmdRequest

// uint32 Timer = 1;
inline void CmdRequest::clear_timer() {
  timer_ = 0u;
}
inline ::google::protobuf::uint32 CmdRequest::timer() const {
  // @@protoc_insertion_point(field_get:SocketData.CmdRequest.Timer)
  return timer_;
}
inline void CmdRequest::set_timer(::google::protobuf::uint32 value) {
  
  timer_ = value;
  // @@protoc_insertion_point(field_set:SocketData.CmdRequest.Timer)
}

// bytes Content = 2;
inline void CmdRequest::clear_content() {
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CmdRequest::content() const {
  // @@protoc_insertion_point(field_get:SocketData.CmdRequest.Content)
  return content_.GetNoArena();
}
inline void CmdRequest::set_content(const ::std::string& value) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SocketData.CmdRequest.Content)
}
#if LANG_CXX11
inline void CmdRequest::set_content(::std::string&& value) {
  
  content_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:SocketData.CmdRequest.Content)
}
#endif
inline void CmdRequest::set_content(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SocketData.CmdRequest.Content)
}
inline void CmdRequest::set_content(const void* value, size_t size) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SocketData.CmdRequest.Content)
}
inline ::std::string* CmdRequest::mutable_content() {
  
  // @@protoc_insertion_point(field_mutable:SocketData.CmdRequest.Content)
  return content_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CmdRequest::release_content() {
  // @@protoc_insertion_point(field_release:SocketData.CmdRequest.Content)
  
  return content_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CmdRequest::set_allocated_content(::std::string* content) {
  if (content != NULL) {
    
  } else {
    
  }
  content_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), content);
  // @@protoc_insertion_point(field_set_allocated:SocketData.CmdRequest.Content)
}

// -------------------------------------------------------------------

// CmdResponse

// bool Status = 1;
inline void CmdResponse::clear_status() {
  status_ = false;
}
inline bool CmdResponse::status() const {
  // @@protoc_insertion_point(field_get:SocketData.CmdResponse.Status)
  return status_;
}
inline void CmdResponse::set_status(bool value) {
  
  status_ = value;
  // @@protoc_insertion_point(field_set:SocketData.CmdResponse.Status)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace SocketData

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_SendCmd_2eproto
