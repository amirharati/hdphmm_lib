// file: $isip/class/system/Error/ErrorMessages.h
// version: $Id: ErrorMessages.h 10636 2007-01-26 22:18:09Z tm334 $
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// make sure definitions are only made once
//
#ifndef ISIP_ERROR_MESSAGES
#define ISIP_ERROR_MESSAGES

// isip include files
//
#ifndef ISIP_ERROR
#include <Error.h>
#endif

// define the error code messages. this file also serves as the
// complete registry to keep error codes unique across the entire ISIP
// environment. in general, each library is assigned a range of 10000
// error codes. within the library's range, each class is assigned
// one or more blocks of 100 error codes.
//
// the first error code assigned to each class should be "xxx class
// general error", so higher level codes can sensibly propagate
// errors. the constant this->ERR should be set to this error code,
// for instance SofList::ERR will point to "SofList class general
// error"
//
static unichar Error_messages[][Error::ERROR_MESSAGE_SIZE] = {

  //--------------------------------------------
  //
  // General purpose errors: range 0 - 999
  //
  //--------------------------------------------

  // file errors
  //
  L"00000000", L"No such file or directory",
  L"00000001", L"I/O Error",
  L"00000002", L"Permission denied",
  L"00000003", L"File seek error",
  L"00000004", L"Attempt to write to a closed file",
  L"00000005", L"Attempt to read from a closed file",
  L"00000006", L"File write error",
  L"00000007", L"File read error",
  L"00000008", L"Attempt to modify a read only file",
  L"00000011", L"Cannot lock a read only file",
  L"00000012", L"Cannot acquire file lock",
  L"00000013", L"Cannot unlock file",
  L"00000014", L"File already open",
  L"00000015", L"Error expanding filename",
  L"00000021", L"Undefined environmental variable",
  L"00000024", L"System call error",
  L"00000025", L"General diagnostic program failure",
  
  // coding errors
  //
  L"00000041", L"Error modifying internal data structure",
  L"00000045", L"This constructor should not be called",
  L"00000050", L"Error cleaning up in destructor",
  L"00000051", L"Unknown clear mode",
  L"00000052", L"Invalid argument",
  L"00000053", L"Error releasing resources",
  L"00000054", L"Memory corrupt",
  L"00000055", L"No memory available",
  L"00000056", L"Memory buffer overflow",
  L"00000057", L"Allocated a static class",
  L"00000058", L"Template function does not generalize to datatype",
  L"00000059", L"Enumeration value out of range",
  L"00000060", L"Illegal NULL pointer passed as argument to method",
  L"00000061", L"Internal stack exceeded",
  L"00000062", L"This cast overflows the target data type",
  L"00000065", L"Out of bounds",
  L"00000066", L"Feature not implemented yet",
  L"00000075", L"Object allocation mode is incompatible with method called",
  L"00000080", L"Virtual pointer not set",  

  // utility errors
  //
  L"00000500", L"Parameter file not specified",
  L"00000501", L"No input files specified",  
  
  //--------------------------------------------
  //
  // Errors for the system library: range 1000 - 9999
  //
  //--------------------------------------------

  // File class errors
  //
  L"00001000", L"File class general error",
  L"00001001", L"Deleting File object without closing file",
  L"00001002", L"File is not open",
  L"00001003", L"Attempt to reopen a file",
  L"00001004", L"Could not close file",
  L"00001005", L"Could not flush file",
  L"00001006", L"Could not truncate file",
  L"00001007", L"Impossible wrap & indention settings, clearing",
  L"00001008", L"Cannot decode binary mode",
  
  // SysChar errors
  //
  L"00001100", L"SysChar class general error",
  L"00001101", L"Characters are not ascii",
  L"00001102", L"Multi-bit UTF8 character encountered, not yet supported",
  L"00001103", L"Multi-bit UTF16 character encountered, not yet supported",
  L"00001104", L"Unknown encoding",

  // MemoryManager errors
  //
  L"00001200", L"MemoryManager class general error",
  L"00001201", L"Attempt to delete non-allocated pointer",
  L"00001202", L"Memory not deleted",
 
  // SysString errors
  //
  L"00001300", L"SysString class general error",

  // Console errors
  //
  L"00001400", L"Console class general error",
  L"00001401", L"Too many open consoles",

  // Integral errors
  //
  L"00001500", L"Integral class general error",

  // Checksum errors
  //
  L"00001600", L"Checksum class general error",
  L"00001601", L"Polynomial specification is incorrect",
  
  // SysHeap errors
  //
  L"00001700", L"SysHeap class general error",
  L"00001701", L"Heap is empty",
  L"00001702", L"Attempt to extract pointer which is not on heap",

  // Error class errors
  //
  L"00001800", L"Error class general error",
  
  // Random class errors
  //
  L"00001900", L"Random class general error",
  
  //--------------------------------------------
  //
  // Errors for the io library: range 10000 - 19999
  //
  //--------------------------------------------

  // Sof errors
  //
  L"00010000", L"Sof class general error",
  L"00010001", L"Not an Sof file",
  L"00010002", L"Object not found",
  L"00010003", L"Tag not found",
  L"00010011", L"Error updating Sof headers",
  L"00010012", L"Error updating Sof file structure",
  L"00010015", L"Error closing file",
  L"00010020", L"Out of object's range",
  L"00010021", L"No current position set",
  L"00010042", L"IEEE floating point standard not supported on architecture",
  L"00010043", L"Error reading Sof header",
  L"00010044", L"File type mismatch",
  L"00010045", L"Invalid data in Sof file structure",
  L"00010051", L"Error writing ASCII label to Sof file",
  L"00010061", L"Too many implicitly tagged objects in file",
  L"00010062", L"Attempt to use a reserved Sof tag",
  L"00010063", L"No implicitly numbered tags allowed in binary files",
  L"00010070", L"Attempting regular i/o in partial mode",
  L"00010071", L"Attempting a resize while not in partial mode",
  
  // SofList errors
  //
  L"00010100", L"SofList class general error",
  L"00010102", L"Symbol error",
  L"00010104", L"Copy Error",
  L"00010105", L"Delete Error",
  L"00010106", L"Could not add to index",
  L"00010107", L"Object already in index",
  L"00010108", L"Current node not set",

  // SofSymbolTable errors
  //
  L"00010200", L"SofSymbolTable class general error",
  L"00010201", L"Could not add to symbol table",
  L"00010202", L"Name not found in symbol table",
  L"00010203", L"Transform vector not defined",
  L"00010204", L"Symbol index out of range",

  // SofParser errors
  //
  L"00010300", L"SofParser class general error",
  L"00010301", L"Insufficient memory for parse",
  L"00010302", L"Attempt to parse empty object",
  L"00010303", L"Error parsing statement",
  L"00010304", L"Error parsing lvalue",
  L"00010305", L"Error parsing rvalue",
  L"00010306", L"Offset out of range",

  // NameMap errors
  //
  L"00010400", L"NameMap class general error",
  L"00010401", L"Integer out of range",
  L"00010402", L"Name not found",
  L"00010403", L"Checksum error",
  
  //--------------------------------------------
  //
  // Errors for the math library: range 20000 - 29999
  //
  //--------------------------------------------

  // scalar errors
  //
  L"00020000", L"MScalar<> class general error",
  L"00020100", L"Boolean class general error",
  L"00020200", L"Byte class general error",
  L"00020300", L"Char class general error",
  L"00020400", L"Ushort class general error",
  L"00020500", L"Ulong class general error",
  L"00020600", L"Ullong class general error",
  L"00020700", L"Short class general error",
  L"00020800", L"Long class general error",
  L"00020900", L"Llong class general error",
  L"00021000", L"Float class general error",
  L"00021100", L"Double class general error",
  L"00021200", L"String class general error",
  L"00021300", L"ComplexFloat class general error",
  L"00021400", L"ComplexDouble class general error",
  L"00021500", L"ComplexLong class general error",
  L"00021600", L"MComplexScalar class general error",

  // vector errors
  //
  L"00022000", L"MVector<> class general error",
  L"00022001", L"invalid length for operation",

  L"00022100", L"VectorByte class general error",
  L"00022200", L"VectorUshort class general error",
  L"00022300", L"VectorUlong class general error",
  L"00022400", L"VectorUllong class general error",
  L"00022500", L"VectorShort class general error",
  L"00022600", L"VectorLong class general error",
  L"00022700", L"VectorLlong class general error",
  L"00022800", L"VectorFloat class general error",
  L"00022900", L"VectorDouble class general error",
  L"00023000", L"VectorComplexFloat class general error",
  L"00023100", L"VectorComplexDouble class general error",
  L"00023200", L"VectorComplexLong class general error",

  // matrix errors
  //
  L"00024000", L"MMatrix class general error",
  L"00024001", L"Invalid operation for matrix type",
  L"00024002", L"Invalid matrix dimension",
  L"00024003", L"Invalid type specified",
  L"00024004", L"Matrix is a singular matrix",
  L"00024005", L"Matrix is not a positive definite matrix",    
  
  L"00024100", L"MatrixByte class general error",
  L"00024200", L"MatrixUshort class general error",
  L"00024300", L"MatrixUlong class general error",
  L"00024400", L"MatrixUllong class general error",
  L"00024500", L"MatrixShort class general error",
  L"00024600", L"MatrixLong class general error",
  L"00024700", L"MatrixLlong class general error",
  L"00024800", L"MatrixFloat class general error",
  L"00024900", L"MatrixDouble class general error",
  L"00025000", L"MatrixComplexFloat class general error",
  L"00025100", L"MatrixComplexDouble class general error",
  L"00025200", L"MatrixComplexLong class general error",

  //--------------------------------------------
  //
  // Errors for the numeric library: range 35000 - 39999
  //
  //--------------------------------------------

  // Sigmoid errors
  //
  L"00035000", L"Sigmoid class general error",
  
  // LinearAlgebra errors
  //
  L"00035100", L"LinearAlgebra class general error",
  L"00035101", L"Singular or near-singular matrix - resorting to SVD solution",
  
  // NonlinearOptimization errors
  //
  L"00035200", L"NonlinearOptimization class general error",
  L"00035201", L"Error in Levenberg-Marquardt optimization",
  
  // Bark errors
  //
  L"00035300", L"Bark class general error",
  
  // Mel errors
  //
  L"00035400", L"Mel class general error",
  
  // Bessel errors
  //
  L"00035500", L"Bessel class general error",
  L"00035501", L"Unsupported Bessel function order",
  
  // Chebyshev errors
  //
  L"00035600", L"Chebyshev class general error",
  
  // Kernel errors
  //
  L"00035700", L"Kernel class general error",
  L"00035701", L"Error in kernel design parameters",
  L"00035702", L"Unknown kernel function specified",
  
  //--------------------------------------------
  //
  // Errors for the dstr library: range 40000 - 44999
  //
  //--------------------------------------------

  // Node errors
  //
  L"00040000", L"Node class general error",
  L"00040001", L"Attempt to use a NULL object",

  // SingleLinkedNode errors
  //
  L"00040100", L"SingleLinkedNode class general error",

  // DoubleLinkedNode errors
  //
  L"00040200", L"DoubleLinkedNode class general error",
  
  // SingleLinkedList errors
  //
  L"00040300", L"SingleLinkedList class general error",
  
  // DoubleLinkedList errors
  //
  L"00040400", L"DoubleLinkedList class general error",
  
  // Stack errors
  //
  L"00040500", L"Stack class general error",
  L"00040501", L"Illegal operation attempted on empty stack",
  
  // Queue errors
  //
  L"00040600", L"Queue class general error",
  L"00040601", L"Illegal operation attempted on empty queue",

  // HashNode errors
  //
  L"00040700", L"HashNode class general error",

  // HashTable errors
  //
  L"00040800", L"HashTable class general error",

  // Vector errors
  //
  L"00040900", L"Vector class general error",
  L"00040901", L"Vector class write error",
  
  // GraphArc errors
  //
  L"00041000", L"GraphArc class general error",

  // GraphVertex errors
  //
  L"00041100", L"GraphVertex class general error",
  L"00041101", L"The item or the subgraph must be set prior to this operation",
  L"00041102", L"No parent graph is attached to this vertex",

  // Graph errors
  //
  L"00041200", L"Graph class general error",
  L"00041201", L"Arc creates an epsilon cycle in the graph",
  L"00041202", L"Attempt to add arc connecting to a vertex in another graph",

  // Tree errors
  //
  L"00041300", L"Tree class general error",

  // CircularBuffer errors
  //
  L"00041600", L"CircularBuffer class general error",
  L"00041601", L"Adding to a full buffer",

  // Pair errors
  //
  L"00041800", L"Pair class general error",

  // Triple errors
  //
  L"00041900", L"Triple class general error",

  // DstrBase errors
  //
  L"00042000", L"DstrBase class general error",

  // Wrapper errors
  //
  L"00042100", L"Wrapper class general error",
  L"00042101", L"Method not defined by wrapper",

  // Set errors
  //
  L"00042200", L"Set class general error",

  //--------------------------------------------
  //
  // Errors for the shell library: range 45000 - 49999
  //
  //--------------------------------------------

  // CommandLine errors
  //
  L"00045000", L"CommandLine class general error",
  L"00045001", L"Option not found",
  L"00045002", L"Ambiguous partial completion for option",
  L"00045003", L"User specified option multiple times",
  L"00045004", L"Programmer specified option multiple times",
  L"00045005", L"Option requires argument",
  L"00045006", L"Command line has not been parsed",

  // Filename errors
  //
  L"00045200", L"Filename class general error",

  // Sdb errors
  //
  L"00045300", L"Sdb class general error",
  L"00045301", L"Not a Sdb file",

  // Parser errors
  //
  L"00045400", L"Parser class general error",
  L"00045401", L"State parsing problem",

  // DebugLevel errors
  //
  L"00045500", L"DebugLevel class general error",
  
  //--------------------------------------------
  //
  // Errors for the multimedia library: range 50000 - 59999
  //
  //--------------------------------------------

  // AudioFile errors
  //
  L"00050000", L"AudioFile class general error",
  L"00050001", L"Error file type",
  L"00050002", L"Bad AR coefficient",
  L"00050003", L"Attempt to open a non-raw audio file using pipe",
  L"00050004", L"Incorrect pipe mode",
  L"00050005", L"This operation is not necessary, ignored",

  // JSGFParser errors
  //
  L"00050100", L"JSGFParser class general error",

  // JSGFToken Errors
  //
  L"00050200", L"JSGFToken class general error",
  
  // AlgorithmData errors
  //
  L"00050300", L"AlgorithmData class general error",
  L"00050301", L"Type mismatch",

  // FeatureFile errors
  //
  L"00050400", L"FeatureFile class general error",

  // TranscriptionDatabase errors
  //
  L"00050500", L"TranscriptionDatabase class general error",

  // NGramParser errors
  //
  L"00050600", L"NGramParser class general error",
  L"00050601", L"incorrect order",
  L"00050602", L"incorrect tag",
  L"00050603", L"unrecognized symbol",
  L"00050604", L"hash table pointer is NULL",
  L"00050605", L"incorrect format",
  L"00050606", L"incorrect grammar number",
  
  // NGramNode errors
  //
  L"00050700", L"NGramNode class general error",

  // SegmentConcat errors
  //
  L"00050800", L"SegmentConcat class general error",

  // XMLToken errors
  //
  L"00050900", L"XMLToken class general error",
  
  // XMLParser errors
  //
  L"00050950", L"XMLParser class general error",
  L"00050951", L"Expat Parse Failed. Check document for well-formedness.",
  
  //--------------------------------------------
  //
  // Errors for the stat library: range 60000 - 69999
  //
  //--------------------------------------------

  // GaussianModel errors
  //
  L"00060100", L"GaussianModel class general error",
  
  // MixtureModel errors
  //
  L"00060200", L"MixtureModel class general error",
  
  // StatisticalModel errors
  //
  L"00060300", L"StatisticalModel class general error",
  L"00060301", L"StatisticalModelBase class general error",
  
  // SupportVectorModel errors
  //
  L"00060350", L"SupportVectorModel class general error",
  
  // UniformModel errors
  //
  L"00060400", L"UniformModel class general error",
  
  // Histogram errors
  //
  L"00060500", L"Histogram class general error",
  L"00060501", L"Bins must be set before computing a histogram",

  // NGramModel errors
  //
  L"00060600", L"NGramModel class general error",
  
  //--------------------------------------------
  //
  // Errors for the algo library: range 70000 - 79999
  //
  //--------------------------------------------

  // AlgorithmBase errors
  //  fundamental errors shared by all algo classes
  //
  L"00070000", L"AlgorithmBase class general error",
  L"00070001", L"Unknown algorithm",
  L"00070002", L"Unknown implementation",
  L"00070003", L"Unknown data type",
  L"00070004", L"Unsupported algorithm",
  L"00070005", L"Unsupported implementation",
  L"00070006", L"Unsupported mode",
  L"00070007", L"Insufficient amount of data",
  L"00070008", L"Incorrect analysis order",
  L"00070009", L"Unknown coefficient type",
  L"00070010", L"Algorithm computation fails",
  
  // Algorithm errors
  //
  L"00070050", L"Algorithm class general error",

  // Correlation errors
  //
  L"00070100", L"Correlation class general error",
  L"00070101", L"Input should be a combination of two signals",
  L"00070102", L"No enough data",
  L"00070102", L"Stability checking fails",

  // Calculus errors
  //
  L"00070200", L"Calculus class general error",
  L"00070201", L"Denominator can't be zero",
  
  // Cepstrum errors
  //
  L"00070300", L"Cepstrum class general error",
  
  // Covariance errors
  //
  L"00070400", L"Covariance class general error",
  
  // Energy errors
  //
  L"00070500", L"Energy class general error",
  
  // Filter errors
  //
  L"00070600", L"Filter class general error",
  L"00070601", L"AR filter must be causal (invalid lag)",
  L"00070602", L"Not enough data provided for non-causal filter",
  
  // FilterBank errors
  //
  L"00070700", L"FilterBank class general error",
  
  // FourierTransform errors
  //
  L"00070800", L"FourierTransform class general error",
  L"00070801", L"Error initializing transform",
  L"00070802", L"Error specified output length under SYMMETRIC mode",
  L"00070803", L"Error complex input under SYMMETRIC mode",
  
  // Generator errors
  //
  L"00070900", L"Generator class general error",
  L"00070901", L"Algorithm parameter mismatch",
  L"00070902", L"Necessary data not specified",
  L"00070903", L"Sampling frequency is zero",
  L"00070904", L"Sampling frequency is set different value with the system",  
  L"00070905", L"The integration upsampling factor is less than 1",  

  // Reflection errors
  //
  L"00071000", L"Reflection class general error",
  L"00071001", L"Dynamic range cannot be greater than zero",  
  L"00071002", L"Beta value cannot be less than zero",
  L"00071003", L"Energy value cannot be less than zero",
  L"00071004", L"Prediction error power cannot be less than zero",  
  
  // Prediction errors
  //
  L"00071100", L"Prediction class general error",
  L"00071101", L"Dynamic range cannot be greater than zero",  
  L"00071102", L"Beta value cannot be less than zero",
  L"00071103", L"Energy value cannot be less than zero",
  L"00071104", L"Prediction error power cannot be less than zero",
  
  // Mask errors
  //
  L"00071200", L"Mask class general error",

  // Math errors
  //
  L"00071300", L"Math class general error",
  L"00071301", L"Unknown function specified",
  L"00071302", L"Unknown operation specified",
  L"00071303", L"Specified function is not defined for this data type",
  L"00071304", L"Mismatch between data types for specified operation",
  
  // Output errors
  //
  L"00071400", L"Output class general error",
  
  // CoefficientLabel errors
  //
  L"00071500", L"CoefficientLabel class general error",
  
  // Spectrum errors
  //
  L"00071600", L"Spectrum class general error",

  // Statistics errors
  //
  L"00071800", L"Statistics class general error",
  
  // Window errors
  //
  L"00072000", L"Window class general error",
  L"00072001", L"Error in window design parameters",
  
  // Connection errors
  //
  L"00072100", L"Connection class general error",
  L"00072101", L"Inputs have different length",
  
  // LogAreaRatio errors
  //
  L"00073000", L"LogAreaRatio class general error",

  // DisplayData errors
  //
  L"00073100", L"DisplayData class general error",

  // AlgorithmContainer errors
  //
  L"00073200", L"AlgorithmContainer class general error",

  // KalmanFilter errors
  //
  L"00073300", L"KalmanFilter class general error",
  L"00073301", L"dimension mismatch with data members",
  L"00073302", L"parameter data members not intialized properly",

  // ParticleFilter errors
  //
  L"00073350", L"ParticleFilter class general error",
  L"00073351", L"dimension mismatch with data members",
  L"00073352", L"incorrect particle count",
  
  // Rps errors
  //
  L"00073400", L"Rps class general error",
  L"00073401", L"Not enough input length",
  L"00073402", L"SVD window size cannot be less than embed dimension",
  L"00073403", L"Embed dimension cannot be less than one",
  
  // Lyapunov errors
  //
  L"00073500", L"Lyapunov class general error",
  L"00073501", L"Number of subgroups cannot be more than number of neighbors",
  L"00073502", L"Number of neighbors not sufficient to compute tangent matrix",
  L"00073503", L"Global dimension cannot be less than local embedding dimension",
  
  // CorrelationIntegral errors
  //
  L"00073600", L"CorrelationIntegral class general error",
  L"00073601", L"Unknown algorithm",
  L"00073602", L"Unknown coefficient type",
  L"00073603", L"The lower bound on the neighborhood radius must be a positive non-zero number",
  L"00073604", L"The upper bound on the neighborhood radius must be a positive non-zero number",
  L"00073605", L"The neighborhood resolution must be a positive non-zero number",
  L"00073606", L"Upper bound for the neighborhood radius must be greater than the lower bound",
  L"00073607", L"The vector containing epsilon values can not be of length zero",
  
  // MutualInformation errors
  //
  L"00073700", L"MutualInformation class general error",
  L"00073701", L"Input should be a combination of two signals",
  L"00073702", L"No enough data",

  // CorrelationEntropy errors
  //
  L"00073800", L"CorrelationEntropy class general error",
  L"00073801", L"Unknown algorithm",
  L"00073802", L"Unknown coefficient type",
  L"00073803", L"Neighborhood radius, epsilon must be a positive non zero number",
  L"00073804", L"Minimum embedding dimension must be less than or equal to the maximum embedding dimension",

  // CorrelationDimension errors
  //
  L"00073900", L"CorrelationDimension class general error",
  L"00073901", L"The lower bound on the neighborhood radius must be a positive non-zero number",
  L"00073902", L"The upper bound on the neighborhood radius must be a positive non-zero number",
  L"00073903", L"the neighbourhood resolution must be positive non-zero number",
  L"00073904", L"Upper bound of the neighbourhood radius muct be greater than lower bound",
  L"00073905", L"Delta cannot be larger than minimum epsilon",
  L"00073906", L"Delta cannot be larger than maximum epsilon",

  //--------------------------------------------
  //
  // Errors for the sp library: range 80000 - 89999
  //
  //--------------------------------------------

  // AudioFrontEnd errors
  //
  L"00080000", L"AudioFrontEnd class general error",
  L"00080001", L"Output must be type VectorFloat",
  L"00080002", L"Empty file or not enough data in file",
  
  // Component errors
  //
  L"00080100", L"Component class general error",
  
  // FrontEnd errors
  //
  L"00080200", L"FrontEnd class general error",
  L"00080250", L"FrontEndBase class general error",
  L"00080260", L"FrontEndUndefined class general error",
  
  // FtrBuffer errors
  //
  L"00080300", L"FtrBuffer class general error",
  
  // Recipe errors
  //
  L"00080400", L"Recipe class general error",
  L"00080401", L"Multiple component paths exist to output",
  L"00080402", L"No component path exists to output",

  // SignalDetector errors
  //
  L"00080500", L"Recipe class general error",
  L"00080510", L"Audio buffer overflow",
  L"00080520", L"Energy buffer overflow",
  L"00080530", L"Zero crossing buffer overflow",
  L"00080540", L"Out of bounds",
  
  //--------------------------------------------
  //
  // Errors for the search library: range 90000 - 99999
  //
  //--------------------------------------------

  // Trace errors
  //
  L"00090000", L"Trace class general error",
  L"00090001", L"Trace class i/o error",
  
  // History errors
  //
  L"00090100", L"History class general error",

  // Hypothesis errors
  //
  L"00090200", L"Hypothesis class general error",
  L"00090201", L"Hypothesis class i/o error",

  // SearchNode errors
  //
  L"00090300", L"SearchNode class general error",

  // SearchSymbol errors
  //
  L"00090400", L"SearchSymbol class general error",

  // SearchLevel errors
  //
  L"00090500", L"SearchLevel class general error",
  
  // LexicalTree errors
  //
  L"00090600", L"LexicalTree class general error",
  
  // HierarchicalSearch errors
  //
  L"00090700", L"HierarchicalSearch class general error",
  L"00090701", L"Number of levels must be greater than zero",

  // StackSearch errors
  //
  L"00090800", L"HierarchicalSearch class general error",
  L"00090801", L"Number of levels must be greater than zero",

  //--------------------------------------------
  //
  // Errors for the pr library: range 100000 - 110000
  //
  //--------------------------------------------

  // HiddenMarkovModel errors
  //
  L"00100000", L"HiddenMarkovModel class general error",
  L"00100050", L"Only Gaussian mixtures are supported for adaptation",

  // LanguageModel errors
  //
  L"00100100", L"LanguageModel class general error",
  
  // DecisionTreeBase errors
  //  fundamental errors shared by all DecisionTree classes
  //
  L"00100200", L"DecisionTreeBase class general error",

  // PhoneticDecisionTree errors
  //
  L"00100300", L"PhoneticDecisionTree class general error",
  
  // PhoneticDecisionTreeNode errors
  //
  L"00100400", L"PhoneticDecisionTreeNode class general error",

  // RegressionDecisionTree errors
  //
  L"00100500", L"RegressionDecisionTree class general error",
  L"00100501", L"RegressionDecisionTree class adapt no gaussian",
  L"00100502", L"Unsupported algorithm or implementation",
  
  // RegressionDecisionTreeNode errors
  //
  L"00100600", L"RegressionDecisionTreeNode class general error",
  L"00100601", L"RegressionDecisionTreeNode class adapt no gaussian",

  // MaximumLikelihoodLinearRegression errors
  //
  L"00100700", L"MaximumLikelihoodLinearRegression class general error",
  L"00100701", L"Unsupported algorithm or implementation",
  
  // StatisticalModelAdaptation errors
  //
  L"00100750", L"StatisticalModelAdaptation class general error",
  L"00100751", L"Unsupported algorithm or implementation",    

  // LanguageModelXML errors
  //
  L"00100800", L"LanguageModelXML class general error",
  L"00100801", L"Context mapping requires symbol table and none is present",
  L"00100802", L"Cannot align graphs because lengths of symbol table, graph list, and graph name list are not equal",
  L"00100803", L"Symbol not found in graph name list",
  L"00100804", L"Invalid symbol",
  L"00100805", L"Error reading symbol type",
  L"00100806", L"Error storing context into vector",
  L"00100807", L"Context grammar may only contain 1 symbol",
  L"00100808", L"Error tokenizing context index from G_X symbol",
  L"00100809", L"Error storing Vector of Contexts into HierarchicalDigraph",
  L"00100810", L"Context already exists with a different index",
  L"00100811", L"Context already exists with the same index",
  L"00100812", L"Error opening temporary file",
  L"00100813", L"debugSearchMethod called with no grammar loaded",
  L"00100814", L"debugTargetMethod called with no grammar loaded",
  L"00100815", L"Invalid token in repeat attribute value",
  L"00100816", L"Grammar start tag not found",
  L"00100817", L"Grammar end tag not found",
  L"00100818", L"The following grammar tag contains no rules: ",
  L"00100819", L"Grammar format contains errors",
  L"00100820", L"Cannot find referenced rule",
  L"00100821", L"Non-local rule references are not currently supported",
  L"00100822", L"One-of tags must contain at least 1 item",
  L"00100823", L"Rule must contain at least 1 item",
  L"00100824", L"Token value set to 'handled', but no procedure is defined for this value",
  L"00100825", L"This special rule is not currently supported",
  L"00100826", L"Error storing vertex",
  
  //--------------------------------------------
  //
  // Errors for the asr library: range 110000 - 119999
  //
  //--------------------------------------------

  // SpeechRecognizer errors
  //
  L"00110000", L"SpeechRecognizer class general error",
  
  // end of list (zero length string) of errors
  //
  L""};

// end of include file
//
#endif
#endif
