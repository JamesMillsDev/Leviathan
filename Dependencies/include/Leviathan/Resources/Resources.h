#pragma once

#include <Leviathan/Leviathan.h>

#include <Leviathan/Resources/Resource.h>

#include <Leviathan/Utils/Singleton.h>

#include <map>
#include <stdexcept>
#include <string>

using std::map;
using std::runtime_error;
using std::string;

namespace Leviathan
{
    class Resources final : public Singleton<Resources>
    {
    public:
        template <typename ASSET, Derived<Resource<ASSET>> RESOURCE>
        static RESOURCE* Find(string _id);

        DLL void OnCreate() override;
        DLL void OnDestroy() override;

    protected:
        DLL static string PathFromID(const string& _id);

    private:
        map<string, string> m_paths;
        map<string, void*> m_resources;

    private:
        template <typename ASSET, Derived<Resource<ASSET>> RESOURCE>
        static RESOURCE* TryGetResource(string& _id);

        DLL void LocateFiles(string _path, string _extensions);
        DLL bool HasResource(const string& _id) const;

        DLL static Resources* GetInstance();
    };

    template <typename ASSET, Derived<Resource<ASSET>> RESOURCE>
    RESOURCE* Resources::Find(string _id)
    {
        return dynamic_cast<RESOURCE*>(TryGetResource<ASSET, RESOURCE>(_id));
    }

    template <typename ASSET, Derived<Resource<ASSET>> RESOURCE>
    RESOURCE* Resources::TryGetResource(string& _id)
    {
        string path = PathFromID(_id);
        if (!path.empty())
        {
            if (!GetInstance()->HasResource(_id))
                GetInstance()->m_resources[_id] = new RESOURCE(path);

            return (RESOURCE*)GetInstance()->m_resources[_id];
        }

        throw runtime_error("No resource with id '" + _id + "' found!");
    }

}