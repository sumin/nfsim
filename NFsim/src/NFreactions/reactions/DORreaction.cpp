


#include "reaction.hh"


using namespace std;
using namespace NFcore;


//should also accept list of local functions and list of PointerNames for each of the functions...
DORRxnClass::DORRxnClass(
		string name,
		double baseRate,
		TransformationSet *transformationSet,
		vector <LocalFunction *> &lfList,
		vector <string> &lfArgumentPointerNameList) :
	ReactionClass(name,baseRate,transformationSet)
{
	cout<<"ok, here we go..."<<endl;
	vector <TemplateMolecule *> dorMolecules;

	//Step 1: Find the DOR reactant, and make sure there is only one.  DOR reactants
	//can be found because they have a LocalFunctionPointer Transformation that keeps
	//information about the pointer onto either a reactant species or a particular molecule
	//in the pattern.
	this->DORreactantIndex = -1;
	for(int r=0; (unsigned)r<n_reactants; r++) {
		for(int i=0; i<transformationSet->getNumOfTransformations(r); i++) {
			Transformation *transform = transformationSet->getTransformation(r,i);
			cout<<"found transformation of type: "<<transform->getType()<<" for reactant: "<<r<<endl;
			if((unsigned)transform->getType()==TransformationFactory::LOCAL_FUNCTION_REFERENCE) {
				if(DORreactantIndex==-1) { DORreactantIndex=r; }
				else if(DORreactantIndex!=r) {
					cout<<"Error when creating DORRxnClass: "<<name<<endl;
					cout<<"DOR reactions currently only support one DOR reactant.  This means that you can"<<endl;
					cout<<"only have a pointer to one or the other of the two reactants, but not both."<<endl;
					exit(1);
				}
			}
		}
	}
	if(DORreactantIndex==-1) {
		cout<<"Error when creating DORRxnClass: "<<name<<endl;
		cout<<"You don't have any pointers onto the Molecules or Species, so you can't have a local function!"<<endl;
		cout<<"That means that this is not a DOR reaction at all!"<<endl;
		exit(1);
	}

	cout<<"I determined that the DOR reactant is in fact: "<<DORreactantIndex<<endl;

	cout<<"N_reactants: "<<transformationSet->getNreactants();



	cout<<endl<<endl<<endl;
	//Step 2: Some bookkeeping so that we can quickly get the function values from a mapping set
	// Now that we have found the DOR reactant, which can potentially have multiple functions, lets
	// figure out which functions apply to which
	// vector <int> indexIntoMappingSet;  //list of the index into the transformations for each of the local functions
	//vector <double> localFunctionValue;  //list of the value of each of the local functions needed to evaluate
	                                    //the rate law


	//Array to double check that we have used all pointer references we have created
	bool *hasMatched = new bool [transformationSet->getNumOfTransformations(DORreactantIndex)];
	for(int i=0; i<transformationSet->getNumOfTransformations(DORreactantIndex); i++) hasMatched[i]=false;

	//make sure that we have the right number of functions and argument names
	if(lfList.size()!=lfArgumentPointerNameList.size()) {
		cout<<"Error when creating DORRxnClass: "<<name<<endl;
		cout<<"LocalFunctionList size and LocalFunctionArguementPointerNameList size do not match!"<<endl;
		exit(1);
	}
	for(int i=0; i<(signed)lfList.size(); i++) {
		cout<<"Received local function: "<< lfList.at(i)->getNiceName()<<endl;
		cout<<" Takes as argument this thang: "<< lfArgumentPointerNameList.at(i)<<endl;

		//Now search for the function argument...
		bool match = false;
		for(int k=0; k<transformationSet->getNumOfTransformations(DORreactantIndex); k++) {
			Transformation *transform = transformationSet->getTransformation(DORreactantIndex,k);
			if((unsigned)transform->getType()==TransformationFactory::LOCAL_FUNCTION_REFERENCE) {
				LocalFunctionReference *lfr = static_cast<LocalFunctionReference*>(transform);
				if(lfr->getPointerName()==lfArgumentPointerNameList.at(i)) {
					cout<<"Found a match here!"<<endl;
					//If we got here, we found a match, so remember the index of the transformation
					//so we can quickly get the value of the function for any mapping object we try
					//to push on the reactant Tree.
					this->lfList.push_back(lfList.at(i));
					localFunctionValue.push_back(0);
					indexIntoMappingSet.push_back(k);
					hasMatched[k]=true;
					match=true;
				}
			}
		}
		if(!match){  //If there was no match found, then we've got issues...
			cout<<"Error when creating DOR reaction: "<<name<<endl;
			cout<<"Could not find a match in the templateMolecules for the pointer reference to species/molecule: ";
			cout<<lfArgumentPointerNameList.at(i)<<endl;
			exit(1);
		}
	}

	//Just send out a warning if we didn't use one of the pointer references we were given
	for(int k=0; k<transformationSet->getNumOfTransformations(DORreactantIndex); k++) {
		Transformation *transform = transformationSet->getTransformation(DORreactantIndex,k);
		if((unsigned)transform->getType()==TransformationFactory::LOCAL_FUNCTION_REFERENCE) {
			if(!hasMatched[k]) {
				cout<<endl<<"Warning!  when creating DORrxnClass: "<<name<<endl;
				cout<<"Pointer reference: "<<  static_cast<LocalFunctionReference*>(transform)->getPointerName() <<endl;
	}	}	}


	cout<<endl<<endl<<"got here, at least."<<endl;
	//exit(1);


}
DORRxnClass::~DORRxnClass() {


}

void DORRxnClass::init() {



}


bool DORRxnClass::tryToAdd(Molecule *m, unsigned int reactantPos) {
	if(reactantPos==this->DORreactantIndex) {

		ReactantList * rl = new ReactantList(DORreactantIndex,transformationSet,25);
		MappingSet *ms = rl->pushNextAvailableMappingSet();
		bool match = this->reactantTemplates[DORreactantIndex]->compare(m,ms);
		cout<<"first, did we match?:"<<match<<endl;
		cout<<"now, let us evaluate!"<<endl;
		evaluateLocalFunctions(ms);
	}


}




//This function takes a given mappingset and looks up the
double DORRxnClass::evaluateLocalFunctions(MappingSet *ms)
{
	//Go through each function, and set the value of the function
	for(int i=0; i<(signed)lfList.size(); i++) {
		Molecule *molObject = ms->get(this->indexIntoMappingSet.at(i))->getMolecule();
		int index = lfList.at(i)->getIndexOfTypeIFunctionValue(molObject);
		this->localFunctionValue.at(i)=molObject->getLocalFunctionValue(index);
		cout<<"found that local function: "<<getName()<<" evaluates to: " <<localFunctionValue.at(i)<<endl;
	}

}
