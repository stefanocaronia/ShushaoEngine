#pragma once

#include <string>
#include <vector>

namespace se {

    /*
        interface Resources
        per gli object che possono essere caricati da disco dalla classe Resources
    */
	class Resource {
        public:
            virtual bool Load(std::string) = 0;
			virtual bool LoadEmbedded(int IDRES) = 0;
			virtual bool LoadBytes(std::vector<char> data) = 0;
    };
}