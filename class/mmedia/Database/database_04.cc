// file: $isip/class/
// version: $Id: database_04.cc 7/10/2013
//

// isip include files
//
#include "Database.h"

//------------------------------------------------------------------------
//
// specific public methods
//
//-----------------------------------------------------------------------


// method: init
//
// arguments:
//  String fname: (input) input file name 
//
// return: a bool8 indicating status
//
// this method initilize the database
//

bool8 Database::init(String fname){

  Sof sof_a;

  filename_d = fname;

  // open the Sof file
  //
  if (sof_a.open(filename_d, File::READ_ONLY) != true) {
    return Error::handle(filename_d, L"open", Error::TEST, __FILE__, __LINE__);
  }

  // set number of records
  //
  records_no_d = sof_a.getCount(PARAM_RECORD);

  // set buffer size
  //
  if (records_no_d < MAX_BUFF_SIZE)
    buff_size_d = records_no_d;
  else
    buff_size_d = MAX_BUFF_SIZE;

  data_d.setCapacity(buff_size_d);
  labels_d.setCapacity(buff_size_d);

  fnames_d.setCapacity(buff_size_d);
  
  // set indices
  //
  current_index_d = 0;
  first_index_d = 0;
  last_index_d = 0;

  // read the info header
  //
   if(read(sof_a,0,L"info") != true)
     return Error::handle(filename_d, L"read", Error::TEST, __FILE__, __LINE__);

   //   if ( database_type_d == DIRECT){
     // read the frist record to determine the dimension
     //
     if(read(sof_a,0,PARAM_RECORD) != true)
       return Error::handle(filename_d, L"read", Error::TEST, __FILE__, __LINE__);
     
     dim_d = data_temp_d.getNumRows();
     //}
  
  sof_a.close();
  
  // read data into buffer
  //
  if(readFrom() != true)
    return Error::handle(filename_d, L"readFrom", Error::TEST, __FILE__, __LINE__);
 

  // exit gracefully
  // 
  return true;

}

// method: readFrom
//
// arguments: 
//  long offset : (input) offset from the begining
//
// return: a bool8 indicating status
//
// this method read data from file
//

bool8 Database::readFrom(long offset){
  
  //local  variables
  //
  long index = offset;
  long index_count = 0;
  Sof  sof_a;
  first_index_d = offset;
  // open the Sof file
  //
  if (sof_a.open(filename_d, File::READ_ONLY) != true) {
    return Error::handle(filename_d, L"open", Error::TEST, __FILE__, __LINE__);
  }

  while (1){

    // read  records
    //
    if(read(sof_a,index) != true)
      return Error::handle(filename_d, L"read", Error::TEST, __FILE__, __LINE__);
    
    // add to buffer
    //
    data_d.append(data_temp_d);
    labels_d.append(labels_temp_d);
    fnames_d.append(fname_temp_d);
    
    last_index_d = index;
    index++;
    index_count++;
    
    if (index_count >= buff_size_d || index >= records_no_d)
      break; 
  }

  sof_a.close();
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  
//
// return: a bool8 indicating status
//
// this method return data sucessively from database
// the result is saved in curr_data and curr_labels
//

bool8 Database::get(){

  // reterive the data from the buffer
  //
  data_d.getElement(curr_data_d,current_index_d);
  labels_d.getElement(curr_labels_d,current_index_d);
  fnames_d.getElement(curr_fname_d,current_index_d);
  
  current_index_d++;
  if ( current_index_d > last_index_d-first_index_d){
   
    // if number of data records is smaller than buffer size just return to the begining
    //
    if ( records_no_d <= buff_size_d )
      current_index_d = 0;
    else{

      // free the buffers
      //
      data_d.setRead(data_d.getNumElements());
      labels_d.setRead(labels_d.getNumElements());
      fnames_d.setRead(fnames_d.getNumElements());
      
      // point current index to the begining of the buffer
      // 
      current_index_d=0;
      if (last_index_d < records_no_d-1){
	
	// read from file
	//
	if(readFrom(last_index_d+1) != true)
	  return Error::handle(filename_d, L"readFrom", Error::TEST, __FILE__, __LINE__);
      }
      else{
	last_index_d = 0;
	if (readFrom() != true)
	  return Error::handle(filename_d, L"readFrom", Error::TEST, __FILE__, __LINE__);

      }

      
    }

  }

  return true;
}


// method: get
//
// arguments:
// index : index of data point 
//
// return: a bool8 indicating status
//
// this method return data sucessively from database
// the result is saved in curr_data and curr_labels
//

bool8 Database::get(int32 index){

  if (index <= last_index_d && index >= first_index_d){
    // reterive the data from the buffer
    //
    data_d.getElement(curr_data_d,index-first_index_d);
    labels_d.getElement(curr_labels_d,index-first_index_d);
    fnames_d.getElement(curr_fname_d,index-first_index_d);
  }
  else if (index > last_index_d){
   
      // free the buffers
      //
      data_d.setRead(data_d.getNumElements());
      labels_d.setRead(labels_d.getNumElements());
      fnames_d.setRead(fnames_d.getNumElements());
      
      if (last_index_d < records_no_d-1){
	
	// read from file
	//
	if(readFrom(last_index_d+1) != true)
	  return Error::handle(filename_d, L"readFrom", Error::TEST, __FILE__, __LINE__);
      }
      
      // reterive the data from the buffer recureseively
      //
      get(index);
  }

  if (index < first_index_d){

    // free the buffers
    //
    data_d.setRead(data_d.getNumElements());
    labels_d.setRead(labels_d.getNumElements());
    fnames_d.setRead(fnames_d.getNumElements()); 
    // read from file
    //
    if(readFrom(0) != true)
      return Error::handle(filename_d, L"readFrom", Error::TEST, __FILE__, __LINE__);
      
  
    // reterive the data from the buffer recursively
    //
    get(index);
    
  }

  return true;
}

// method: put
//
// arguments:
//  
//
// return: a bool8 indicating status
//
// this method put a record in a file
//

bool8 Database::put(Sof & sof_a){

  // write in the sof file
  //
  if(! write(sof_a,current_index_d))
    return Error::handle(name(), L"write", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);
  current_index_d++;

  return true;
}


// method: read_HTK
//
// arguments:
//  
//
// return: a bool8 indicating status
//
// this method read HTK format from files
//
bool8 Database::read_HTK(String filename,int32 start_frame,int32 end_frame){
  
  // debug
  //end_frame=end_frame-1;
  // if (start_frame >= end_frame){
  // printf("start_frame error %d %d\n",start_frame,end_frame);
  // filename.debug(L"filename");
  // end_frame=start_frame;
  //}
  File fp;
  fp.open(filename,File::READ_ONLY,File::BINARY);
  fp.setBMode(File::SWAP);
  
  // local variables
  //
  int32 num_frames,tmp;
  fp.read(&num_frames,sizeof(num_frames),1);
  
  double frame_interval;  // msec
  fp.read(&tmp,sizeof(tmp),1);

  
  frame_interval = (double)tmp*0.0001;
  db_fr_d = frame_interval;
  
  int16 byte_per_frame;
  fp.read(&byte_per_frame,sizeof(byte_per_frame),1);
  
  int16 type_code;
  fp.read(&type_code,sizeof(type_code),1);
  if (type_code <0)
    type_code = type_code + 65536;


  // number of  bits for base type
  //
  int32 ndt = 6;
  
  // list of suffix codes
  //
  String cc;
  cc.assign(L"ENDACZK0VT");
  int32 nhb;
  // number of suffix code
  // 
  nhb = cc.length();

  
  VectorLong hb(nhb+1),hd(nhb);
  for(int32 i = 0 ; i < nhb+1; i++)
    hb(i) = floor((double)type_code*(double)pow(2,-(ndt+nhb-i)));
  
  for (int32 i = 0; i < nhb; i++){
    hd(i) = hb(nhb-i)-2*hb(nhb-i-1);
  }

  int32 dt;
  
  dt = type_code - (pow(2,ndt)*hb(nhb));

  // Current version can't read wav(0), IREFC(5) and DISCRETE (10)
  // 
  if (dt == 0 || dt == 5 || dt == 10){
    //error
  } else{

    // if it is compressed
    //
    if (hd(4) == 1){
      num_frames = num_frames - 4;
      int32 ncol = byte_per_frame / 2;
      data_temp_d.setDimensions(ncol,end_frame-start_frame+1);
      VectorFloat scales(ncol),biases(ncol);
      int16 temp;
      for (int32 i = 0 ; i < ncol;i++){
	fp.read(& scales(i),sizeof(float32),1);
      }
      for (int32 i = 0 ; i < ncol;i++){
	fp.read(& biases(i),sizeof(float32),1);
      }
      fp.seek(ncol*(start_frame)*sizeof(int16),File::POS_PLUS_CUR);
      for (int32 i = 0 ; i < end_frame-start_frame+1; i++){
	for ( int32 j = 0; j < ncol; j++){
          fp.read(&temp,sizeof(int16),1);
	  data_temp_d.setValue(j,i,((double)temp+biases(j))*(1/scales(j)));
	}
      }
    }
    else{ //uncompresses

      int32 ncol = byte_per_frame / 4;
      int16 temp;
      data_temp_d.setDimensions(ncol,end_frame-start_frame+1);
      
      fp.seek(ncol*(start_frame-1)*sizeof(int16),File::POS_PLUS_CUR);
      for (int32 i = 0 ; i < end_frame-start_frame+1; i++){
	for ( int32 j = 0; j < ncol; j++){
          fp.read(&temp,sizeof(int16),1);
	  data_temp_d.setValue(j,i,(double)temp);
	}
      }
    }

  }
  
  fp.close();
  // return gracefully
  //
  return true;
}





