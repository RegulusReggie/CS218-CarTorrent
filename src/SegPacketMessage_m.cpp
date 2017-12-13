//
// Generated file, do not edit! Created by nedtool 5.2 from src/SegPacketMessage.msg.
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
#include "SegPacketMessage_m.h"

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

Register_Class(SegPacketMessage)

SegPacketMessage::SegPacketMessage(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    this->segNum = 0;
    this->numSegs = 0;
    data_arraysize = 0;
    this->data = 0;
}

SegPacketMessage::SegPacketMessage(const SegPacketMessage& other) : ::WaveShortMessage(other)
{
    data_arraysize = 0;
    this->data = 0;
    copy(other);
}

SegPacketMessage::~SegPacketMessage()
{
    delete [] this->data;
}

SegPacketMessage& SegPacketMessage::operator=(const SegPacketMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void SegPacketMessage::copy(const SegPacketMessage& other)
{
    this->packetId = other.packetId;
    this->segNum = other.segNum;
    this->numSegs = other.numSegs;
    delete [] this->data;
    this->data = (other.data_arraysize==0) ? nullptr : new unsigned char[other.data_arraysize];
    data_arraysize = other.data_arraysize;
    for (unsigned int i=0; i<data_arraysize; i++)
        this->data[i] = other.data[i];
}

void SegPacketMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->packetId);
    doParsimPacking(b,this->segNum);
    doParsimPacking(b,this->numSegs);
    b->pack(data_arraysize);
    doParsimArrayPacking(b,this->data,data_arraysize);
}

void SegPacketMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->packetId);
    doParsimUnpacking(b,this->segNum);
    doParsimUnpacking(b,this->numSegs);
    delete [] this->data;
    b->unpack(data_arraysize);
    if (data_arraysize==0) {
        this->data = 0;
    } else {
        this->data = new unsigned char[data_arraysize];
        doParsimArrayUnpacking(b,this->data,data_arraysize);
    }
}

const char * SegPacketMessage::getPacketId() const
{
    return this->packetId.c_str();
}

void SegPacketMessage::setPacketId(const char * packetId)
{
    this->packetId = packetId;
}

int SegPacketMessage::getSegNum() const
{
    return this->segNum;
}

void SegPacketMessage::setSegNum(int segNum)
{
    this->segNum = segNum;
}

int SegPacketMessage::getNumSegs() const
{
    return this->numSegs;
}

void SegPacketMessage::setNumSegs(int numSegs)
{
    this->numSegs = numSegs;
}

void SegPacketMessage::setDataArraySize(unsigned int size)
{
    unsigned char *data2 = (size==0) ? nullptr : new unsigned char[size];
    unsigned int sz = data_arraysize < size ? data_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        data2[i] = this->data[i];
    for (unsigned int i=sz; i<size; i++)
        data2[i] = 0;
    data_arraysize = size;
    delete [] this->data;
    this->data = data2;
}

unsigned int SegPacketMessage::getDataArraySize() const
{
    return data_arraysize;
}

unsigned char SegPacketMessage::getData(unsigned int k) const
{
    if (k>=data_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    return this->data[k];
}

void SegPacketMessage::setData(unsigned int k, unsigned char data)
{
    if (k>=data_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    this->data[k] = data;
}

class SegPacketMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SegPacketMessageDescriptor();
    virtual ~SegPacketMessageDescriptor();

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

Register_ClassDescriptor(SegPacketMessageDescriptor)

SegPacketMessageDescriptor::SegPacketMessageDescriptor() : omnetpp::cClassDescriptor("SegPacketMessage", "WaveShortMessage")
{
    propertynames = nullptr;
}

SegPacketMessageDescriptor::~SegPacketMessageDescriptor()
{
    delete[] propertynames;
}

bool SegPacketMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SegPacketMessage *>(obj)!=nullptr;
}

const char **SegPacketMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SegPacketMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SegPacketMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int SegPacketMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *SegPacketMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetId",
        "segNum",
        "numSegs",
        "data",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int SegPacketMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetId")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "segNum")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSegs")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SegPacketMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
        "int",
        "unsigned char",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **SegPacketMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *SegPacketMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int SegPacketMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SegPacketMessage *pp = (SegPacketMessage *)object; (void)pp;
    switch (field) {
        case 3: return pp->getDataArraySize();
        default: return 0;
    }
}

const char *SegPacketMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SegPacketMessage *pp = (SegPacketMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SegPacketMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SegPacketMessage *pp = (SegPacketMessage *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getPacketId());
        case 1: return long2string(pp->getSegNum());
        case 2: return long2string(pp->getNumSegs());
        case 3: return ulong2string(pp->getData(i));
        default: return "";
    }
}

bool SegPacketMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SegPacketMessage *pp = (SegPacketMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setPacketId((value)); return true;
        case 1: pp->setSegNum(string2long(value)); return true;
        case 2: pp->setNumSegs(string2long(value)); return true;
        case 3: pp->setData(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *SegPacketMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *SegPacketMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SegPacketMessage *pp = (SegPacketMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


