#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H
#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;
class TextureHolder
{
private:
    map<string, Texture> m_Textures;

    // ��������� �����������, ����� ������������� �������� ������� ��� ������
    TextureHolder() {}

public:
    // ������� ����������� � ������������, ����� ������������� �������� �����
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder& operator=(const TextureHolder&) = delete;

    // ������������ ����� ��� ��������� ���������� ������ (Singleton)
    static TextureHolder& getInstance() {
        static TextureHolder instance;
        return instance;
    }

    // ����������� ����� ��� ������� � ��������
    static Texture& GetTexture(string const& filename) {
        return getInstance().loadTexture(filename);
    }

private:
    // ����� ��� �������� ��������
    Texture& loadTexture(const string& filename) {
        auto keyValuePair = m_Textures.find(filename);
        if (keyValuePair != m_Textures.end()) {
            return keyValuePair->second;
        }
        else {
            auto& texture = m_Textures[filename];
            texture.loadFromFile(filename);
            return texture;
        }
    }
};
#endif