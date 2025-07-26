#pragma once
#include <string>
class User
{
  private:
    std::string name;  // 用户名

  public:
    User() = default;

    // 获取用户名
    std::string getName() const
    {
        return name;
    }

    // 设置用户名
    void setName(const std::string &newName)
    {
        name = newName;
    }
};