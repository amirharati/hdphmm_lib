// file: $isip/class/io/SofList/SofNode.h
// version: $Id: SofNode.h 5118 2000-10-03 12:59:38Z picone $
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// make sure definitions are only made once
//
#ifndef ISIP_SOF_NODE
#define ISIP_SOF_NODE

// SofNode: a structure containing an entry for an object
//
typedef struct sof_index_node SofNode;

struct sof_index_node {
  int32 name_d;				// object name 
  int32 tag_d;				// object tag
  int32 pos_d;				// position of data in the file
  int32 size_d;				// size in bytes of data

  // for the tree
  //
  SofNode* parent_d;
  SofNode* left_d;
  SofNode* right_d;
};

// end of include file
//
#endif
#endif
