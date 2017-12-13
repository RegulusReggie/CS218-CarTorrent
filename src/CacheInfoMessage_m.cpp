//
// Generated file, do not edit! Created by nedtool 5.2 from src/CacheInfoMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "CacheInfoMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(CacheInfoMessage)

CacheInfoMessage::CacheInfoMessage(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    info_arraysize = 0;
    this->info = 0;
    file_arraysize = 0;
    this->file = 0;
}

CacheInfoMessage::CacheInfoMessage(const CacheInfoMessage& other) : ::WaveShortMessage(other)
{
    info_arraysize = 0;
    this->info = 0;
    file_arraysize = 0;
    this->file = 0;
    copy(other);
}

CacheInfoMessage::~CacheInfoMessage()
{
    delete [] this->info;
    delete [] this->file;
}

CacheInfoMessage& CacheInfoMessage::operator=(const CacheInfoMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void CacheInfoMessage::copy(const CacheInfoMessage& other)
{
    delete [] this->info;
    this->info = (other.info_arraysize==0) ? nullptr : new InfoEntry[other.info_arraysize];
    info_arraysize = other.info_arraysize;
    for (unsigned int i=0; i<info_arraysize; i++)
        this->info[i] = other.info[i];
    delete [] this->file;
    this->file = (other.file_arraysize==0) ? nullptr : new FileEntry[other.file_arraysize];
    file_arraysize = other.file_arraysize;
    for (unsigned int i=0; i<file_arraysize; i++)
        this->file[i] = other.file[i];
}

void CacheInfoMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    b->pack(info_arraysize);
    doParsimArrayPacking(b,this->info,info_arraysize);
    b->pack(file_arraysize);
    doParsimArrayPacking(b,this->file,file_arraysize);
}

void CacheInfoMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    delete [] this->info;
    b->unpack(info_arraysize);
    if (info_arraysize==0) {
        this->info = 0;
    } else {
        this->info = new InfoEntry[info_arraysize];
        doParsimArrayUnpacking(b,this->info,info_arraysize);
    }
    delete [] this->file;
    b->unpack(file_arraysize);
    if (file_arraysize==0) {
        this->file = 0;
    } else {
        this->file = new FileEntry[file_arraysize];
        doParsimArrayUnpacking(b,this->file,file_arraysize);
    }
}

void CacheInfoMessage::setInfoArraySize(unsigned int size)
{
    InfoEntry *info2 = (size==0) ? nullptr : new InfoEntry[size];
    unsigned int sz = info_arraysize < size ? info_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        info2[i] = this->info[i];
    info_arraysize = size;
    delete [] this->info;
    this->info = info2;
}

unsigned int CacheInfoMessage::getInfoArraySize() const
{
    return info_arraysize;
}

InfoEntry& CacheInfoMessage::getInfo(unsigned int k)
{
    if (k>=info_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", info_arraysize, k);
    return this->info[k];
}

void CacheInfoMessage::setInfo(unsigned int k, const InfoEntry& info)
{
    if (k>=info_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", info_arraysize, k);
    this->info[k] = info;
}

void CacheInfoMessage::setFileArraySize(unsigned int size)
{
    FileEntry *file2 = (size==0) ? nullptr : new FileEntry[size];
    unsigned int sz = file_arraysize < size ? file_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        file2[i] = this->file[i];
    file_arraysize = size;
    delete [] this->file;
    this->file = file2;
}

unsigned int CacheInfoMessage::getFileArraySize() const
{
    return file_arraysize;
}

FileEntry& CacheInfoMessage::getFile(unsigned int k)
{
    if (k>=file_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", file_arraysize, k);
    return this->file[k];
}

void CacheInfoMessage::setFile(unsigned int k, const FileEntry& file)
{
    if (k>=file_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", file_arraysize, k);
    this->file[k] = file;
}

class CacheInfoMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CacheInfoMessageDescriptor();
    virtual ~CacheInfoMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CacheInfoMessageDescriptor)

CacheInfoMessageDescriptor::CacheInfoMessageDescriptor() : omnetpp::cClassDescriptor("CacheInfoMessage", "WaveShortMessage")
{
    propertynames = nullptr;
}

CacheInfoMessageDescriptor::~CacheInfoMessageDescriptor()
{
    delete[] propertynames;
}

bool CacheInfoMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CacheInfoMessage *>(obj)!=nullptr;
}

const char **CacheInfoMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CacheInfoMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CacheInfoMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CacheInfoMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CacheInfoMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "info",
        "file",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CacheInfoMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "info")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "file")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CacheInfoMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "InfoEntry",
        "FileEntry",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CacheInfoMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CacheInfoMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CacheInfoMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CacheInfoMessage *pp = (CacheInfoMessage *)object; (void)pp;
    switch (field) {
        case 0: return pp->getInfoArraySize();
        case 1: return pp->getFileArraySize();
        default: return 0;
    }
}

const char *CacheInfoMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CacheInfoMessage *pp = (CacheInfoMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CacheInfoMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CacheInfoMessage *pp = (CacheInfoMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getInfo(i); return out.str();}
        case 1: {std::stringstream out; out << pp->getFile(i); return out.str();}
        default: return "";
    }
}

bool CacheInfoMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CacheInfoMessage *pp = (CacheInfoMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CacheInfoMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(InfoEntry));
        case 1: return omnetpp::opp_typename(typeid(FileEntry));
        default: return nullptr;
    };
}

void *CacheInfoMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CacheInfoMessage *pp = (CacheInfoMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getInfo(i)); break;
        case 1: return (void *)(&pp->getFile(i)); break;
        default: return nullptr;
    }
}


