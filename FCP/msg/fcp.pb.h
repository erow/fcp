// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fcp.proto

#ifndef PROTOBUF_fcp_2eproto__INCLUDED
#define PROTOBUF_fcp_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_fcp_2eproto();
void protobuf_InitDefaults_fcp_2eproto();
void protobuf_AssignDesc_fcp_2eproto();
void protobuf_ShutdownFile_fcp_2eproto();

class FcpMessage;

enum FcpMessage_FcpType {
  FcpMessage_FcpType_POSTUP = 0,
  FcpMessage_FcpType_POSTDOWN = 1,
  FcpMessage_FcpType_EXTPOST = 4,
  FcpMessage_FcpType_SUBSCRIBE = 2,
  FcpMessage_FcpType_UNSUBSCRIBE = 3,
  FcpMessage_FcpType_FcpMessage_FcpType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  FcpMessage_FcpType_FcpMessage_FcpType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool FcpMessage_FcpType_IsValid(int value);
const FcpMessage_FcpType FcpMessage_FcpType_FcpType_MIN = FcpMessage_FcpType_POSTUP;
const FcpMessage_FcpType FcpMessage_FcpType_FcpType_MAX = FcpMessage_FcpType_EXTPOST;
const int FcpMessage_FcpType_FcpType_ARRAYSIZE = FcpMessage_FcpType_FcpType_MAX + 1;

const ::google::protobuf::EnumDescriptor* FcpMessage_FcpType_descriptor();
inline const ::std::string& FcpMessage_FcpType_Name(FcpMessage_FcpType value) {
  return ::google::protobuf::internal::NameOfEnum(
    FcpMessage_FcpType_descriptor(), value);
}
inline bool FcpMessage_FcpType_Parse(
    const ::std::string& name, FcpMessage_FcpType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<FcpMessage_FcpType>(
    FcpMessage_FcpType_descriptor(), name, value);
}
// ===================================================================

class FcpMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:FcpMessage) */ {
 public:
  FcpMessage();
  virtual ~FcpMessage();

  FcpMessage(const FcpMessage& from);

  inline FcpMessage& operator=(const FcpMessage& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FcpMessage& default_instance();

  static const FcpMessage* internal_default_instance();

  void Swap(FcpMessage* other);

  // implements Message ----------------------------------------------

  inline FcpMessage* New() const { return New(NULL); }

  FcpMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FcpMessage& from);
  void MergeFrom(const FcpMessage& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(FcpMessage* other);
  void UnsafeMergeFrom(const FcpMessage& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef FcpMessage_FcpType FcpType;
  static const FcpType POSTUP =
    FcpMessage_FcpType_POSTUP;
  static const FcpType POSTDOWN =
    FcpMessage_FcpType_POSTDOWN;
  static const FcpType EXTPOST =
    FcpMessage_FcpType_EXTPOST;
  static const FcpType SUBSCRIBE =
    FcpMessage_FcpType_SUBSCRIBE;
  static const FcpType UNSUBSCRIBE =
    FcpMessage_FcpType_UNSUBSCRIBE;
  static inline bool FcpType_IsValid(int value) {
    return FcpMessage_FcpType_IsValid(value);
  }
  static const FcpType FcpType_MIN =
    FcpMessage_FcpType_FcpType_MIN;
  static const FcpType FcpType_MAX =
    FcpMessage_FcpType_FcpType_MAX;
  static const int FcpType_ARRAYSIZE =
    FcpMessage_FcpType_FcpType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  FcpType_descriptor() {
    return FcpMessage_FcpType_descriptor();
  }
  static inline const ::std::string& FcpType_Name(FcpType value) {
    return FcpMessage_FcpType_Name(value);
  }
  static inline bool FcpType_Parse(const ::std::string& name,
      FcpType* value) {
    return FcpMessage_FcpType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional string dst_uri = 1;
  void clear_dst_uri();
  static const int kDstUriFieldNumber = 1;
  const ::std::string& dst_uri() const;
  void set_dst_uri(const ::std::string& value);
  void set_dst_uri(const char* value);
  void set_dst_uri(const char* value, size_t size);
  ::std::string* mutable_dst_uri();
  ::std::string* release_dst_uri();
  void set_allocated_dst_uri(::std::string* dst_uri);

  // optional string src_uri = 4;
  void clear_src_uri();
  static const int kSrcUriFieldNumber = 4;
  const ::std::string& src_uri() const;
  void set_src_uri(const ::std::string& value);
  void set_src_uri(const char* value);
  void set_src_uri(const char* value, size_t size);
  ::std::string* mutable_src_uri();
  ::std::string* release_src_uri();
  void set_allocated_src_uri(::std::string* src_uri);

  // optional .FcpMessage.FcpType type = 2;
  void clear_type();
  static const int kTypeFieldNumber = 2;
  ::FcpMessage_FcpType type() const;
  void set_type(::FcpMessage_FcpType value);

  // optional string data = 3;
  void clear_data();
  static const int kDataFieldNumber = 3;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  void set_data(const char* value);
  void set_data(const char* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // @@protoc_insertion_point(class_scope:FcpMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr dst_uri_;
  ::google::protobuf::internal::ArenaStringPtr src_uri_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  int type_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_fcp_2eproto_impl();
  friend void  protobuf_AddDesc_fcp_2eproto_impl();
  friend void protobuf_AssignDesc_fcp_2eproto();
  friend void protobuf_ShutdownFile_fcp_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<FcpMessage> FcpMessage_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// FcpMessage

// optional string dst_uri = 1;
inline void FcpMessage::clear_dst_uri() {
  dst_uri_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FcpMessage::dst_uri() const {
  // @@protoc_insertion_point(field_get:FcpMessage.dst_uri)
  return dst_uri_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FcpMessage::set_dst_uri(const ::std::string& value) {
  
  dst_uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:FcpMessage.dst_uri)
}
inline void FcpMessage::set_dst_uri(const char* value) {
  
  dst_uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:FcpMessage.dst_uri)
}
inline void FcpMessage::set_dst_uri(const char* value, size_t size) {
  
  dst_uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:FcpMessage.dst_uri)
}
inline ::std::string* FcpMessage::mutable_dst_uri() {
  
  // @@protoc_insertion_point(field_mutable:FcpMessage.dst_uri)
  return dst_uri_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FcpMessage::release_dst_uri() {
  // @@protoc_insertion_point(field_release:FcpMessage.dst_uri)
  
  return dst_uri_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FcpMessage::set_allocated_dst_uri(::std::string* dst_uri) {
  if (dst_uri != NULL) {
    
  } else {
    
  }
  dst_uri_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), dst_uri);
  // @@protoc_insertion_point(field_set_allocated:FcpMessage.dst_uri)
}

// optional string src_uri = 4;
inline void FcpMessage::clear_src_uri() {
  src_uri_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FcpMessage::src_uri() const {
  // @@protoc_insertion_point(field_get:FcpMessage.src_uri)
  return src_uri_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FcpMessage::set_src_uri(const ::std::string& value) {
  
  src_uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:FcpMessage.src_uri)
}
inline void FcpMessage::set_src_uri(const char* value) {
  
  src_uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:FcpMessage.src_uri)
}
inline void FcpMessage::set_src_uri(const char* value, size_t size) {
  
  src_uri_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:FcpMessage.src_uri)
}
inline ::std::string* FcpMessage::mutable_src_uri() {
  
  // @@protoc_insertion_point(field_mutable:FcpMessage.src_uri)
  return src_uri_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FcpMessage::release_src_uri() {
  // @@protoc_insertion_point(field_release:FcpMessage.src_uri)
  
  return src_uri_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FcpMessage::set_allocated_src_uri(::std::string* src_uri) {
  if (src_uri != NULL) {
    
  } else {
    
  }
  src_uri_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), src_uri);
  // @@protoc_insertion_point(field_set_allocated:FcpMessage.src_uri)
}

// optional .FcpMessage.FcpType type = 2;
inline void FcpMessage::clear_type() {
  type_ = 0;
}
inline ::FcpMessage_FcpType FcpMessage::type() const {
  // @@protoc_insertion_point(field_get:FcpMessage.type)
  return static_cast< ::FcpMessage_FcpType >(type_);
}
inline void FcpMessage::set_type(::FcpMessage_FcpType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:FcpMessage.type)
}

// optional string data = 3;
inline void FcpMessage::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FcpMessage::data() const {
  // @@protoc_insertion_point(field_get:FcpMessage.data)
  return data_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FcpMessage::set_data(const ::std::string& value) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:FcpMessage.data)
}
inline void FcpMessage::set_data(const char* value) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:FcpMessage.data)
}
inline void FcpMessage::set_data(const char* value, size_t size) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:FcpMessage.data)
}
inline ::std::string* FcpMessage::mutable_data() {
  
  // @@protoc_insertion_point(field_mutable:FcpMessage.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FcpMessage::release_data() {
  // @@protoc_insertion_point(field_release:FcpMessage.data)
  
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FcpMessage::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    
  } else {
    
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:FcpMessage.data)
}

inline const FcpMessage* FcpMessage::internal_default_instance() {
  return &FcpMessage_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::FcpMessage_FcpType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::FcpMessage_FcpType>() {
  return ::FcpMessage_FcpType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_fcp_2eproto__INCLUDED