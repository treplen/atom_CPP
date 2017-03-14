//
// Created by svuatoslav on 3/14/17.
//

#ifndef ARRAY_ARRAYPOINTERBOOL_H
#define ARRAY_ARRAYPOINTERBOOL_H

template <>
class ArrayPointer<bool>
{
private:
    int access[8] = {0b00000001, 0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
    char * data_;
    size_t capacity_;
    size_t links_;
    bool helper_; //i'm useless here...
    bool & ret_val_;
    int index_;
    void _upd();
    inline size_t _capacity();
public:
    bool dislink();//same
    void link();//same
    bool ok() const;//same
    void dump(std::ostream& out,size_t displacement = 0) const;//same
    const uint32_t POISON = UINT32_MAX;
    explicit ArrayPointer(size_t capacity);
    ArrayPointer(const ArrayPointer<bool>&);
    ~ArrayPointer();
    bool& operator[](const size_t); //unsafe
    bool& At(const size_t); //safe
    size_t capacity() const; //same
};


void ArrayPointer<bool>::link()
{
    INFO(*this);
    links_++;
    log("bool add link"+std::to_string(links_));
    INFO(*this);
}

bool ArrayPointer<bool>::dislink()
{
    INFO(*this);
    log("bool rem link"+std::to_string(links_-1));
    INFO(*this);
    return !(--links_);
}

size_t ArrayPointer<bool>::capacity() const
{
    INFO(*this);
    return capacity_;
}
size_t ArrayPointer<bool>::_capacity() {
    return (int)ceil(1. * capacity_ / 8);
}

ArrayPointer<bool>::ArrayPointer(size_t capacity): data_(nullptr), capacity_(capacity), links_(1), helper_(false), ret_val_(helper_), index_(0)
{
    if (capacity == 0) return;
    try
    {
        data_ = new char[_capacity()];
    }
    catch(std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

ArrayPointer<bool>::ArrayPointer(const ArrayPointer<bool> & array_pointer):capacity_(array_pointer.capacity_), links_(1), helper_(false), ret_val_(helper_), index_(0)
{
    try
    {
        int cap = _capacity();
        data_ = new char[cap];
        for (size_t i = 0; i < cap; i++)
            data_[i] = array_pointer.data_[i];
    }
    catch (std::bad_alloc e)
    {
        data_ = nullptr;
        capacity_ = 0;
    }
    INFO(*this);
}

void ArrayPointer<bool>::_upd()
{
    INFO(*this);
    int i = index_ / 8;
    int j = index_ % 8;
    data_ [i] &= ~access[j];
    if (ret_val_) data_ [i] |=access[j];
    INFO(*this);
}

bool& ArrayPointer<bool>::operator[](const size_t index)
{
    INFO(*this);
    _upd();

    index_=index;
    int i = index / 8;
    int j = index % 8;
    char c = data_ [i];
    ret_val_ =(c & access[j]) ? 1:0;
    INFO(*this);
    return ret_val_;
}

bool& ArrayPointer<bool>::At(const size_t index)
{
    INFO(*this);
    _upd();
    if (index<capacity_){
        index_=index;
        int i = index / 8;
        int j = index % 8;
        char c = data_ [i];
        ret_val_ =(c & access[j]) ? 1 : 0;
        INFO(*this);
        return ret_val_;
    }
    INFO(*this);
    throw std::out_of_range("bad value");
}

ArrayPointer<bool>::~ArrayPointer()
{
    INFO(*this);
    delete[] data_;
    log("bool free res");
    data_ = nullptr;
    capacity_ = POISON;
    links_ = POISON;
}

bool ArrayPointer<bool>::ok() const
{
    return (links_ != POISON) && (capacity_ != POISON);
}

void ArrayPointer<bool>::dump(std::ostream& out,size_t displacement) const
{
    char *tabs = utils::getPadding('\t',displacement);

    out<<tabs<<"ArrayPointer("<<(ok()?"OK":"ERROR")<<") @ "<<(void*)this<<'\n';
    out<<tabs<<"{\n";
    out<<tabs<<"\tcapacity: "<<capacity_<<(capacity_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tlinks: "<<links_<<(links_==POISON?" (POISON)":"")<<'\n';
    out<<tabs<<"\tdata @ "<<(void*)data_<<" :\n";
    out<<tabs<<"\t{\n";

    for(int index = 0;index<capacity_;index++){
        int i = index / 8;
        int j = index % 8;
        char c = data_ [i];
        ret_val_ =(c & access[j]) ? 1:0;
        out<<tabs<<"\t\tdata_["<<index<<"] = ";
        out<<ret_val_<<'\n';
    }

    out<<tabs<<"\t}\n";
    out<<tabs<<"}\n";

    delete [] tabs;
}

#endif //ARRAY_ARRAYPOINTERBOOL_H
