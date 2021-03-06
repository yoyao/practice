// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: practice.employee.proto

#ifndef PROTOBUF_practice_2eemployee_2eproto_INCLUDED
#define PROTOBUF_practice_2eemployee_2eproto_INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_practice_2eemployee_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsEmployeeImpl();
void InitDefaultsEmployee();
inline void InitDefaults() {
  InitDefaultsEmployee();
}
}  // namespace protobuf_practice_2eemployee_2eproto
namespace practice {
class Employee;
class EmployeeDefaultTypeInternal;
extern EmployeeDefaultTypeInternal _Employee_default_instance_;
}  // namespace practice
namespace google {
namespace protobuf {
template<> ::practice::Employee* Arena::Create< ::practice::Employee>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace practice {

enum Department {
  NetworkDept = 0,
  MarketDept = 1,
  FinanceDept = 2,
  Department_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Department_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Department_IsValid(int value);
const Department Department_MIN = NetworkDept;
const Department Department_MAX = FinanceDept;
const int Department_ARRAYSIZE = Department_MAX + 1;

const ::google::protobuf::EnumDescriptor* Department_descriptor();
inline const ::std::string& Department_Name(Department value) {
  return ::google::protobuf::internal::NameOfEnum(
    Department_descriptor(), value);
}
inline bool Department_Parse(
    const ::std::string& name, Department* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Department>(
    Department_descriptor(), name, value);
}
enum JobTitle {
  Staffer = 0,
  Leader = 1,
  Director = 2,
  JobTitle_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  JobTitle_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool JobTitle_IsValid(int value);
const JobTitle JobTitle_MIN = Staffer;
const JobTitle JobTitle_MAX = Director;
const int JobTitle_ARRAYSIZE = JobTitle_MAX + 1;

const ::google::protobuf::EnumDescriptor* JobTitle_descriptor();
inline const ::std::string& JobTitle_Name(JobTitle value) {
  return ::google::protobuf::internal::NameOfEnum(
    JobTitle_descriptor(), value);
}
inline bool JobTitle_Parse(
    const ::std::string& name, JobTitle* value) {
  return ::google::protobuf::internal::ParseNamedEnum<JobTitle>(
    JobTitle_descriptor(), name, value);
}
// ===================================================================

class Employee : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:practice.Employee) */ {
 public:
  Employee();
  virtual ~Employee();

  Employee(const Employee& from);

  inline Employee& operator=(const Employee& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Employee(Employee&& from) noexcept
    : Employee() {
    *this = ::std::move(from);
  }

  inline Employee& operator=(Employee&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Employee& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Employee* internal_default_instance() {
    return reinterpret_cast<const Employee*>(
               &_Employee_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Employee* other);
  friend void swap(Employee& a, Employee& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Employee* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<Employee>(NULL);
  }

  Employee* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<Employee>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Employee& from);
  void MergeFrom(const Employee& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Employee* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string empno = 3;
  void clear_empno();
  static const int kEmpnoFieldNumber = 3;
  const ::std::string& empno() const;
  void set_empno(const ::std::string& value);
  #if LANG_CXX11
  void set_empno(::std::string&& value);
  #endif
  void set_empno(const char* value);
  void set_empno(const char* value, size_t size);
  ::std::string* mutable_empno();
  ::std::string* release_empno();
  void set_allocated_empno(::std::string* empno);

  // double salary = 2;
  void clear_salary();
  static const int kSalaryFieldNumber = 2;
  double salary() const;
  void set_salary(double value);

  // int32 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // .practice.Department dept = 4;
  void clear_dept();
  static const int kDeptFieldNumber = 4;
  ::practice::Department dept() const;
  void set_dept(::practice::Department value);

  // .practice.JobTitle jobtitle = 5;
  void clear_jobtitle();
  static const int kJobtitleFieldNumber = 5;
  ::practice::JobTitle jobtitle() const;
  void set_jobtitle(::practice::JobTitle value);

  // @@protoc_insertion_point(class_scope:practice.Employee)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr empno_;
  double salary_;
  ::google::protobuf::int32 id_;
  int dept_;
  int jobtitle_;
  mutable int _cached_size_;
  friend struct ::protobuf_practice_2eemployee_2eproto::TableStruct;
  friend void ::protobuf_practice_2eemployee_2eproto::InitDefaultsEmployeeImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Employee

// int32 id = 1;
inline void Employee::clear_id() {
  id_ = 0;
}
inline ::google::protobuf::int32 Employee::id() const {
  // @@protoc_insertion_point(field_get:practice.Employee.id)
  return id_;
}
inline void Employee::set_id(::google::protobuf::int32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:practice.Employee.id)
}

// double salary = 2;
inline void Employee::clear_salary() {
  salary_ = 0;
}
inline double Employee::salary() const {
  // @@protoc_insertion_point(field_get:practice.Employee.salary)
  return salary_;
}
inline void Employee::set_salary(double value) {
  
  salary_ = value;
  // @@protoc_insertion_point(field_set:practice.Employee.salary)
}

// string empno = 3;
inline void Employee::clear_empno() {
  empno_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Employee::empno() const {
  // @@protoc_insertion_point(field_get:practice.Employee.empno)
  return empno_.GetNoArena();
}
inline void Employee::set_empno(const ::std::string& value) {
  
  empno_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:practice.Employee.empno)
}
#if LANG_CXX11
inline void Employee::set_empno(::std::string&& value) {
  
  empno_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:practice.Employee.empno)
}
#endif
inline void Employee::set_empno(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  empno_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:practice.Employee.empno)
}
inline void Employee::set_empno(const char* value, size_t size) {
  
  empno_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:practice.Employee.empno)
}
inline ::std::string* Employee::mutable_empno() {
  
  // @@protoc_insertion_point(field_mutable:practice.Employee.empno)
  return empno_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Employee::release_empno() {
  // @@protoc_insertion_point(field_release:practice.Employee.empno)
  
  return empno_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Employee::set_allocated_empno(::std::string* empno) {
  if (empno != NULL) {
    
  } else {
    
  }
  empno_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), empno);
  // @@protoc_insertion_point(field_set_allocated:practice.Employee.empno)
}

// .practice.Department dept = 4;
inline void Employee::clear_dept() {
  dept_ = 0;
}
inline ::practice::Department Employee::dept() const {
  // @@protoc_insertion_point(field_get:practice.Employee.dept)
  return static_cast< ::practice::Department >(dept_);
}
inline void Employee::set_dept(::practice::Department value) {
  
  dept_ = value;
  // @@protoc_insertion_point(field_set:practice.Employee.dept)
}

// .practice.JobTitle jobtitle = 5;
inline void Employee::clear_jobtitle() {
  jobtitle_ = 0;
}
inline ::practice::JobTitle Employee::jobtitle() const {
  // @@protoc_insertion_point(field_get:practice.Employee.jobtitle)
  return static_cast< ::practice::JobTitle >(jobtitle_);
}
inline void Employee::set_jobtitle(::practice::JobTitle value) {
  
  jobtitle_ = value;
  // @@protoc_insertion_point(field_set:practice.Employee.jobtitle)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace practice

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::practice::Department> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::practice::Department>() {
  return ::practice::Department_descriptor();
}
template <> struct is_proto_enum< ::practice::JobTitle> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::practice::JobTitle>() {
  return ::practice::JobTitle_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_practice_2eemployee_2eproto_INCLUDED
