// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: data.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "data.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* player_info_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  player_info_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_data_2eproto() {
  protobuf_AddDesc_data_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "data.proto");
  GOOGLE_CHECK(file != NULL);
  player_info_descriptor_ = file->message_type(0);
  static const int player_info_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(player_info, player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(player_info, player_name_),
  };
  player_info_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      player_info_descriptor_,
      player_info::default_instance_,
      player_info_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(player_info, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(player_info, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(player_info));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_data_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    player_info_descriptor_, &player_info::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_data_2eproto() {
  delete player_info::default_instance_;
  delete player_info_reflection_;
}

void protobuf_AddDesc_data_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\ndata.proto\"5\n\013player_info\022\021\n\tplayer_id"
    "\030\001 \002(\005\022\023\n\013player_name\030\002 \002(\t", 67);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "data.proto", &protobuf_RegisterTypes);
  player_info::default_instance_ = new player_info();
  player_info::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_data_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_data_2eproto {
  StaticDescriptorInitializer_data_2eproto() {
    protobuf_AddDesc_data_2eproto();
  }
} static_descriptor_initializer_data_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int player_info::kPlayerIdFieldNumber;
const int player_info::kPlayerNameFieldNumber;
#endif  // !_MSC_VER

player_info::player_info()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void player_info::InitAsDefaultInstance() {
}

player_info::player_info(const player_info& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void player_info::SharedCtor() {
  _cached_size_ = 0;
  player_id_ = 0;
  player_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

player_info::~player_info() {
  SharedDtor();
}

void player_info::SharedDtor() {
  if (player_name_ != &::google::protobuf::internal::kEmptyString) {
    delete player_name_;
  }
  if (this != default_instance_) {
  }
}

void player_info::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* player_info::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return player_info_descriptor_;
}

const player_info& player_info::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_data_2eproto();
  return *default_instance_;
}

player_info* player_info::default_instance_ = NULL;

player_info* player_info::New() const {
  return new player_info;
}

void player_info::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    player_id_ = 0;
    if (has_player_name()) {
      if (player_name_ != &::google::protobuf::internal::kEmptyString) {
        player_name_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool player_info::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 player_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &player_id_)));
          set_has_player_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_player_name;
        break;
      }

      // required string player_name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_player_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_player_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->player_name().data(), this->player_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void player_info::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 player_id = 1;
  if (has_player_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->player_id(), output);
  }

  // required string player_name = 2;
  if (has_player_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->player_name().data(), this->player_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->player_name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* player_info::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 player_id = 1;
  if (has_player_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->player_id(), target);
  }

  // required string player_name = 2;
  if (has_player_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->player_name().data(), this->player_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->player_name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int player_info::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 player_id = 1;
    if (has_player_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->player_id());
    }

    // required string player_name = 2;
    if (has_player_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->player_name());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void player_info::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const player_info* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const player_info*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void player_info::MergeFrom(const player_info& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_player_id()) {
      set_player_id(from.player_id());
    }
    if (from.has_player_name()) {
      set_player_name(from.player_name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void player_info::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void player_info::CopyFrom(const player_info& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool player_info::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void player_info::Swap(player_info* other) {
  if (other != this) {
    std::swap(player_id_, other->player_id_);
    std::swap(player_name_, other->player_name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata player_info::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = player_info_descriptor_;
  metadata.reflection = player_info_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
