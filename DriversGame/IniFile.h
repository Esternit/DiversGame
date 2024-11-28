
#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using KeysMap = std::map<std::string, std::string>;
using SectionsMap = std::map<std::string, KeysMap>;

const std::vector<std::string> trueValues = { "true", "yes", "y", "1" };

/// ����� ��� ������ � ������� ������������ ������� .ini
class IniFile
{
public:
    /// �����������
    /// @param fileName ���� �� ����� ������������
    explicit IniFile(const std::string& path);
    /// ����������
    /// @note ������ �������������� ���� ����������� �������������
    ~IniFile();

    /// ������ ������������ ������������ � ����
    void save();

    /// ������ �������� ���� int
    /// @param section ������ ini-�����
    /// @param key ���� � ������
    /// @param def �������� �� ���������, ������������ � ������ ���������
    /// �����/������
    int readInt(const std::string& section, const std::string& key, int def = 0);
    /// ������ �������� ���� double
    double readDouble(const std::string& section, const std::string& key,
        double def = 0);

    float readFloat(const std::string& section, const std::string& key,
        float def = 0);
    /// ������ �������� ���� std::string
    std::string readString(const std::string& section, const std::string& key,
        const std::string& def = "");
    /// ������ �������� ���� bool
    /// @note ��� ������ ������ ������ �������������� �� ����� ��������� ��
    /// trueValues, ���������� �� ��������
    /// @note � ��������� ������� - ������������ false
    bool readBool(const std::string& section, const std::string& key,
        bool def = false);

    std::vector<std::string> getSectionsNames();

    ///// ������ �������� ���� int
    //void writeInt(const std::string& section, const std::string& key, int value);
    ///// ������ �������� ���� double
    //void writeDouble(const std::string& section, const std::string& key,
    //    double value);
    ///// ������ �������� ���� std::string
    //void writeString(const std::string& section, const std::string& key,
    //    const std::string& value);
    ///// ������ �������� ���� bool
    //void writeBool(const std::string& section, const std::string& key,
    //    bool value);

    /// �������� ������������� ������
    bool isSectionExist(const std::string& section);
    /// �������� ������������� ����� � ������
    bool isKeysExist(const std::string& section, const std::string& key);

    /// ��������� ���������� ������
    size_t getSectionsCount();
    /// ��������� ���������� ������ � ������
    size_t getKeysCount(const std::string& section);

    /// ��������� �������� ���� ������
    SectionsMap getSections() const;

    /// �������� ������
    bool deleteSection(const std::string& section);
    /// �������� ����� �� ������
    bool deleteKey(const std::string& section, const std::string& key);

    /// ���������� ����� ������
    bool addNewSection(const std::string& section);
    //int coutnSymbolOccurences(std::string line, char symbol);
    //bool checkSection(std::string section);

private:
    const std::string filePath; ///< ���� �� ����� ������������
    SectionsMap data;           ///< ��������
};

/*
������: ����������� ����� ��� ������ � ������� ������������ ������� .ini ��
������������� ���������� ���� ����� ��������� ������:

[Window]
fullscreen=true
width=1920
height=1080
[Graphics]
; ��������� �������
quality=high ; �������� �������
filtering=x16

���� ����� ���������:
    - ����������� - �� ������� �;� �� ����� ������;
    - ������ - ������, ���������� �������� ������ � ���������� �������;
    - �������� - ������ ���� �����=��������;
    - ������ ������;
    - ��������� ������ - ������ ��� �����, �������� ��� �����, ���� ���
��������, ������������� '[', ']', '=' � �.�.

������ ������� �� ����� ������/�������� ������ �������������
��������� ������ �� ������ ���� ���������� � �������� � ������������
���������� ���������� ������ ������������ � ����
��� ������� ���������� ������ - ������� �������� ���������� �����

������ �������������:
IniFile ini("config.ini");
bool fs = ini.readBool("Window", "fullscreen", false); // true from ini
int uiScale = ini.readInt("Window", "UIScale", 1);    // 1 from default
*/