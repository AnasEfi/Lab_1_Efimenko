#include "CPipe.h"
using namespace std;
Pipe::Pipe()
{
    status = false;
    Name = ""; //�������� �� ���������
}

Pipe::~Pipe()
{
}

std::string Pipe::GetName() const
{
    return Name;
}

void Pipe::SetName(std::string new_name)
{
    Name = new_name;
}
