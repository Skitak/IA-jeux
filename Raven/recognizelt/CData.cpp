#include "CData.h"



//------------------------------------------------------------------------
//
//  constant training data
//------------------------------------------------------------------------

//double InputVectors[NUM_DATAS][NUM_VECTORS]=
//{
//	//50,20//,				//shoot
//	//			
// // 50,20,				//don't shoot
//	//				
//  10,10			//shoot
//
// // 50,20
//}; 
//
//double OutputVectors[NUM_DATAS]={
//1//,0,1,0
//};

const char* Names[NUM_PATTERNS]=
{
	"don't shoot",
	"shoot",
};

//--------------------------------- Init ---------------------------------
//
//  Initializes the appropriate vectors with the const training data
//------------------------------------------------------------------------
void CData::Init()
{
	m_iNumData = NUM_DATAS;
  //for each const pattern  
 // for (int ptn=0; ptn<m_iNumData; ++ptn)
 // {
 //   //add it to the vector of patterns
 //   vector<double> temp;

 //   for (int v=0; v<m_iVectorSize; ++v)
 //   {
 //     temp.push_back(InputVectors[ptn][v]);//on ajoute la ligne de données
 //   }
 //   
 //   m_vecPatterns.push_back(temp);


	//for (int v = 0; v<m_iNumData; ++v)
	//{
	//	m_vecResult.push_back(OutputVectors[v]);//on ajoute la ligne de données
	//}

 // }
  for (int ptn = 0; ptn < NUM_PATTERNS; ++ptn) {
	  //add the name of the pattern
	  m_vecNames.push_back(Names[ptn]);
  }
 
}

// --------------------------- CreateTrainingSetFromData -----------------
//
//  this function creates a training set from the data defined as constants
//  in CData.h. 
//------------------------------------------------------------------------
void CData::CreateTrainingSetFromData()
{
  //empty the vectors
  m_SetIn.clear();
  m_SetOut.clear();
  
  //add each pattern //à remplacer par add each test
  for (int ptn=0; ptn<m_iNumData; ++ptn)
  {    
    //add the data to the training set
    m_SetIn.push_back(m_vecPatterns[ptn]);

    //create the output vector for this pattern. First fill a 
    //std::vector with zeros
    vector<double> outputs(NUM_PATTERNS, 0);

    //set the relevant output to 1
    outputs[m_vecResult[ptn]] = 1;//correspond à l'identifiant 

    //add it to the output set
    m_SetOut.push_back(outputs);
  }
}

//------------------------- PatternName ----------------------------------
//
//  returns the pattern name at the given value
//------------------------------------------------------------------------
string CData::PatternName(int val)
{
  if (m_vecNames.size() > val)
  {
    return m_vecNames[val];
  }

  else
  {
    return "";
  }
}

//pas utilisé
//------------------------- AddData -------------------------------------
//
//  adds a new pattern to data
//-----------------------------------------------------------------------
void CData::AddData(vector<double> &data, double result)
{
  //check that the size is correct
  if (data.size() != m_iVectorSize)
  {
    MessageBox(NULL, "Incorrect Data Size", "Error", MB_OK);
  }

  //add the name
  //m_vecNames.push_back(NewName);
  m_vecResult.push_back(result);

  //add the data
  m_vecPatterns.push_back(data);
  ++m_iNumData;

  //keep a track of number of patterns
  //++m_iNumPatterns;
  
  //create the new training set
  CreateTrainingSetFromData();
}

