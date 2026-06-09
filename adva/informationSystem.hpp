
#if defined(__cpp_modules) && (__cplusplus >= 202302L)
    import std;
#else
    #include <unordered_map>
    #include <string>
    #include <iostream>
#endif

#include "cgen/micros.h"

#pragma once
#ifndef METACORE___ADVA_INFORMATIONSYSTEM_HPP
#define METACORE___ADVA_INFORMATIONSYSTEM_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___ADVA_HPP
namespace adva {
#endif // METACORE___ADVA_HPP

    using std::unordered_map;

    object libInfo
    {
    private:
        unordered_map<str, str> funcInfo;
        unordered_map<str, str> objInfo;
        unordered_map<str, unordered_map<str, str>> objMemInfo;
    public:
        libInfo() = default;
        ~libInfo() = default;

        void addFunc(const str& name,
        const str& description) noexcept {
            funcInfo[name] = description;
        }

        void addObj(const str& name,
        const str& description) noexcept {
            objInfo[name] = description;
            objMemInfo[name] = unordered_map<str, str>();
        }

        void addObj(const str& obj, const str& name,
        const str& description) noexcept {
            (objMemInfo[obj])[name] = description;
        }

        void removeFunc(const str& name) noexcept {
            bool exist = false;
            unordered_map<str, str> result;
            for(auto p : funcInfo) {
                if(p.first != name) {
                    result[p.first] = p.second;
                } else {
                    exist = true;
                }
            }
            if(!exist) {
                std::cout << "this name: " << name
                << " don't exist in the function information map.\n";
            } else {
                funcInfo = result;
            }
        }

        void removeObj(const str& name) noexcept {
            bool exist = false;
            unordered_map<str, str> result;
            for(auto p : objInfo) {
                if(p.first != name) {
                    result[p.first] = p.second;
                } else {
                    exist = true;
                }
            }
            if(!exist) {
                std::cout << "this name: " << name
                << " don't exist in the function information map.\n";
            } else {
                objInfo = result;
            }
        }

        void removeObj(const str& obj, const str& name) noexcept {
            bool exist = false;
            unordered_map<str, str> result;
            for(auto p : objMemInfo[obj]) {
                if(p.first != name) {
                    result[p.first] = p.second;
                } else {
                    exist = true;
                }
            }
            if(!exist) {
                std::cout << "this name: " << name
                << " don't exist in the function information map.\n";
            } else {
                objMemInfo[obj] = result;
            }
        }
    };

    typedef unordered_map<str, libInfo> dirInfo;
    typedef unordered_map<str, dirInfo> info_sys;

    class system64 {};
    
#ifdef METACORE___ADVA_HPP
}
#endif // METACORE___ADVA_HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // METACORE___ADVA_INFORMATIONSYSTEM_HPP