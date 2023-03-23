/*
 * LabelMap.h
 */

#ifndef LABELMAP_H_
#define LABELMAP_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "MstlGraph.h"

namespace GGSXLib{

/*
 * Map strings into integers for efficiency.
 */
class LabelMap: public std::map<std::string, mstl_node_label_t>{
public:

	/*
	 * Return a (new) ID (integer) for the given string (label).
	 */
	mstl_node_label_t getLabel(std::string s){
		LabelMap::iterator IT = this->find(s);
		if(IT == this->end()){
			mstl_node_label_t label = (mstl_node_label_t)this->size();
			this->insert(std::pair<std::string,mstl_node_label_t>(s,label));
			return label;
		}
		else{
			return IT->second;
		}
	}

	mstl_node_label_t *getLabelP(std::string s)
	{
		LabelMap::iterator IT = this->find(s);
		if (IT == this->end())
		{
			mstl_node_label_t label = (mstl_node_label_t)this->size();
			std::pair<std::map<std::string, mstl_node_label_t>::iterator, bool> inserted;
			inserted = this->insert(std::pair<std::string, mstl_node_label_t>(s, label));
			return &(inserted.first->second);
		}
		else
		{
			return &(IT->second);
		}
	}

	/*
	 * Load from file
	 */
	friend std::istream& operator>>(std::istream& is, LabelMap& m){
		size_t size;
		is.read((char*)&size,sizeof(std::size_t));
		for(int i=0;i<size;i++){
			std::string s_label;
			mstl_node_label_t n_label=0;
			std::getline(is, s_label, '\n');
			is.read((char*)&n_label, sizeof(mstl_node_label_t));
			m.insert(std::pair<std::string, mstl_node_label_t>(s_label,n_label));
		}
		return is;
	}
	/*
	 * Save to file
	 */
	friend std::ostream& operator<<(std::ostream& os, LabelMap& m){
		std::size_t size = m.size();
		os.write((char*)&(size), sizeof(std::size_t));
		for(LabelMap::iterator IT = m.begin(); IT!=m.end(); IT++){
			os<< IT->first;
			os<<"\n";
			os.write((char*)&(IT->second), sizeof(mstl_node_label_t));
		}
		os.flush();
		return os;
	}

};

}

#endif /* LABELMAP_H_ */
