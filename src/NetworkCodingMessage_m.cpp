//
// Generated file, do not edit! Created by nedtool 5.2 from src/NetworkCodingMessage.msg.
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
#include "NetworkCodingMessage_m.h"

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

Register_Class(NetworkCodingMessage)

NetworkCodingMessage::NetworkCodingMessage(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    this->fileSize = 0;
    this->gen = 0;
    this->numBlocksGen = 0;
    this->blockSize = 0;
    this->codingNum = 0;
    coeffs_arraysize = 0;
    this->coeffs = 0;
    sums_arraysize = 0;
    this->sums = 0;
}

NetworkCodingMessage::NetworkCodingMessage(const NetworkCodingMessage& other) : ::WaveShortMessage(other)
{
    coeffs_arraysize = 0;
    this->coeffs = 0;
    sums_arraysize = 0;
    this->sums = 0;
    copy(other);
}

NetworkCodingMessage::~NetworkCodingMessage()
{
    delete [] this->coeffs;
    delete [] this->sums;
}

NetworkCodingMessage& NetworkCodingMessage::operator=(const NetworkCodingMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void NetworkCodingMessage::copy(const NetworkCodingMessage& other)
{
    this->packetId = other.packetId;
    this->fileSize = other.fileSize;
    this->gen = other.gen;
    this->numBlocksGen = other.numBlocksGen;
    this->blockSize = other.blockSize;
    this->codingNum = other.codingNum;
    delete [] this->coeffs;
    this->coeffs = (other.coeffs_arraysize==0) ? nullptr : new unsigned char[other.coeffs_arraysize];
    coeffs_arraysize = other.coeffs_arraysize;
    for (unsigned int i=0; i<coeffs_arraysize; i++)
        this->coeffs[i] = other.coeffs[i];
    delete [] this->sums;
    this->sums = (other.sums_arraysize==0) ? nullptr : new unsigned char[other.sums_arraysize];
    sums_arraysize = other.sums_arraysize;
    for (unsigned int i=0; i<sums_arraysize; i++)
        this->sums[i] = other.sums[i];
}

void NetworkCodingMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->packetId);
    doParsimPacking(b,this->fileSize);
    doParsimPacking(b,this->gen);
    doParsimPacking(b,this->numBlocksGen);
    doParsimPacking(b,this->blockSize);
    doParsimPacking(b,this->codingNum);
    b->pack(coeffs_arraysize);
    doParsimArrayPacking(b,this->coeffs,coeffs_arraysize);
    b->pack(sums_arraysize);
    doParsimArrayPacking(b,this->sums,sums_arraysize);
}

void NetworkCodingMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->packetId);
    doParsimUnpacking(b,this->fileSize);
    doParsimUnpacking(b,this->gen);
    doParsimUnpacking(b,this->numBlocksGen);
    doParsimUnpacking(b,this->blockSize);
    doParsimUnpacking(b,this->codingNum);
    delete [] this->coeffs;
    b->unpack(coeffs_arraysize);
    if (coeffs_arraysize==0) {
        this->coeffs = 0;
    } else {
        this->coeffs = new unsigned char[coeffs_arraysize];
        doParsimArrayUnpacking(b,this->coeffs,coeffs_arraysize);
    }
    delete [] this->sums;
    b->unpack(sums_arraysize);
    if (sums_arraysize==0) {
        this->sums = 0;
    } else {
        this->sums = new unsigned char[sums_arraysize];
        doParsimArrayUnpacking(b,this->sums,sums_arraysize);
    }
}

const char * NetworkCodingMessage::getPacketId() const
{
    return this->packetId.c_str();
}

void NetworkCodingMessage::setPacketId(const char * packetId)
{
    this->packetId = packetId;
}

long NetworkCodingMessage::getFileSize() const
{
    return this->fileSize;
}

void NetworkCodingMessage::setFileSize(long fileSize)
{
    this->fileSize = fileSize;
}

int NetworkCodingMessage::getGen() const
{
    return this->gen;
}

void NetworkCodingMessage::setGen(int gen)
{
    this->gen = gen;
}

int NetworkCodingMessage::getNumBlocksGen() const
{
    return this->numBlocksGen;
}

void NetworkCodingMessage::setNumBlocksGen(int numBlocksGen)
{
    this->numBlocksGen = numBlocksGen;
}

int NetworkCodingMessage::getBlockSize() const
{
    return this->blockSize;
}

void NetworkCodingMessage::setBlockSize(int blockSize)
{
    this->blockSize = blockSize;
}

int NetworkCodingMessage::getCodingNum() const
{
    return this->codingNum;
}

void NetworkCodingMessage::setCodingNum(int codingNum)
{
    this->codingNum = codingNum;
}

void NetworkCodingMessage::setCoeffsArraySize(unsigned int size)
{
    unsigned char *coeffs2 = (size==0) ? nullptr : new unsigned char[size];
    unsigned int sz = coeffs_arraysize < size ? coeffs_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        coeffs2[i] = this->coeffs[i];
    for (unsigned int i=sz; i<size; i++)
        coeffs2[i] = 0;
    coeffs_arraysize = size;
    delete [] this->coeffs;
    this->coeffs = coeffs2;
}

unsigned int NetworkCodingMessage::getCoeffsArraySize() const
{
    return coeffs_arraysize;
}

unsigned char NetworkCodingMessage::getCoeffs(unsigned int k) const
{
    if (k>=coeffs_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", coeffs_arraysize, k);
    return this->coeffs[k];
}

void NetworkCodingMessage::setCoeffs(unsigned int k, unsigned char coeffs)
{
    if (k>=coeffs_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", coeffs_arraysize, k);
    this->coeffs[k] = coeffs;
}

void NetworkCodingMessage::setSumsArraySize(unsigned int size)
{
    unsigned char *sums2 = (size==0) ? nullptr : new unsigned char[size];
    unsigned int sz = sums_arraysize < size ? sums_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        sums2[i] = this->sums[i];
    for (unsigned int i=sz; i<size; i++)
        sums2[i] = 0;
    sums_arraysize = size;
    delete [] this->sums;
    this->sums = sums2;
}

unsigned int NetworkCodingMessage::getSumsArraySize() const
{
    return sums_arraysize;
}

unsigned char NetworkCodingMessage::getSums(unsigned int k) const
{
    if (k>=sums_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", sums_arraysize, k);
    return this->sums[k];
}

void NetworkCodingMessage::setSums(unsigned int k, unsigned char sums)
{
    if (k>=sums_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", sums_arraysize, k);
    this->sums[k] = sums;
}

class NetworkCodingMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NetworkCodingMessageDescriptor();
    virtual ~NetworkCodingMessageDescriptor();

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

Register_ClassDescriptor(NetworkCodingMessageDescriptor)

NetworkCodingMessageDescriptor::NetworkCodingMessageDescriptor() : omnetpp::cClassDescriptor("NetworkCodingMessage", "WaveShortMessage")
{
    propertynames = nullptr;
}

NetworkCodingMessageDescriptor::~NetworkCodingMessageDescriptor()
{
    delete[] propertynames;
}

bool NetworkCodingMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NetworkCodingMessage *>(obj)!=nullptr;
}

const char **NetworkCodingMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NetworkCodingMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NetworkCodingMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int NetworkCodingMessageDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *NetworkCodingMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetId",
        "fileSize",
        "gen",
        "numBlocksGen",
        "blockSize",
        "codingNum",
        "coeffs",
        "sums",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int NetworkCodingMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetId")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "fileSize")==0) return base+1;
    if (fieldName[0]=='g' && strcmp(fieldName, "gen")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "numBlocksGen")==0) return base+3;
    if (fieldName[0]=='b' && strcmp(fieldName, "blockSize")==0) return base+4;
    if (fieldName[0]=='c' && strcmp(fieldName, "codingNum")==0) return base+5;
    if (fieldName[0]=='c' && strcmp(fieldName, "coeffs")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "sums")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NetworkCodingMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "long",
        "int",
        "int",
        "int",
        "int",
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **NetworkCodingMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *NetworkCodingMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NetworkCodingMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NetworkCodingMessage *pp = (NetworkCodingMessage *)object; (void)pp;
    switch (field) {
        case 6: return pp->getCoeffsArraySize();
        case 7: return pp->getSumsArraySize();
        default: return 0;
    }
}

const char *NetworkCodingMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NetworkCodingMessage *pp = (NetworkCodingMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NetworkCodingMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NetworkCodingMessage *pp = (NetworkCodingMessage *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getPacketId());
        case 1: return long2string(pp->getFileSize());
        case 2: return long2string(pp->getGen());
        case 3: return long2string(pp->getNumBlocksGen());
        case 4: return long2string(pp->getBlockSize());
        case 5: return long2string(pp->getCodingNum());
        case 6: return ulong2string(pp->getCoeffs(i));
        case 7: return ulong2string(pp->getSums(i));
        default: return "";
    }
}

bool NetworkCodingMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NetworkCodingMessage *pp = (NetworkCodingMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setPacketId((value)); return true;
        case 1: pp->setFileSize(string2long(value)); return true;
        case 2: pp->setGen(string2long(value)); return true;
        case 3: pp->setNumBlocksGen(string2long(value)); return true;
        case 4: pp->setBlockSize(string2long(value)); return true;
        case 5: pp->setCodingNum(string2long(value)); return true;
        case 6: pp->setCoeffs(i,string2ulong(value)); return true;
        case 7: pp->setSums(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *NetworkCodingMessageDescriptor::getFieldStructName(int field) const
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

void *NetworkCodingMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NetworkCodingMessage *pp = (NetworkCodingMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


