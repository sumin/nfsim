#include <iostream>

#include "NFcore.hh"

using namespace std;
using namespace NFcore;


TemplateMolecule::TemplateMolecule(MoleculeType * parentMoleculeType)
{
	if(DEBUG) cout<<"-creating template molecule of type " << parentMoleculeType->getName() << endl;
	this->parentMoleculeType = parentMoleculeType;
	this->parentMoleculeType->addTemplateMolecule(this);
	clear();
}

TemplateMolecule::~TemplateMolecule()
{
	if(DEBUG) cout <<"   -destroying template molecule of type " << parentMoleculeType->getName() << endl;
	
	
	TemplateMapping *tm;
	while(tMappings.size()>0)
	{
		tm = tMappings.back();
		tMappings.pop_back();
		delete tm;
	}
}

void TemplateMolecule::setHasVisited(int bSiteCompareIndex)
{
	hasVisitedBond.at(bSiteCompareIndex) = true;
}

//void TemplateMolecule::addBindingSite(int bSiteIndex)
//{
//	// get the binding site from the MoleculeType
//	this->bSiteIndex.push_back(bSiteIndex); // saves index into bSite array in MoleculeType
////	TemplateSite * b = new TemplateSite(parentMoleculeType->getBindingSiteName(bSiteIndex),this, bonds.size());
//	bonds.push_back(b);
//	hasVisitedBond.push_back(false);
//}


void TemplateMolecule::addStateValue(const char * stateName, int stateValue)
{
	this->addStateValue(parentMoleculeType->getStateIndex(stateName), stateValue);
}

void TemplateMolecule::addStateValue(int stateIndex, int stateValue)
{
	this->stateIndex.push_back(stateIndex);
	this->stateValue.push_back(stateValue);
}

void TemplateMolecule::addNotStateValue(char * stateName, int notStateValue)
{
	this->notStateIndex.push_back(parentMoleculeType->getStateIndex(stateName));
	this->notStateValue.push_back(notStateValue);
}



bool TemplateMolecule::isBindingSiteOpen(int bIndex) const
{
	if(bonds.at(bIndex)==0) return true;
	return false;
}

bool TemplateMolecule::isBindingSiteBonded(int bIndex) const
{
	if(bonds.at(bIndex)==0) return false;
	return true;	
}

TemplateMolecule * TemplateMolecule::getBondedTemplateMolecule(int bIndex) const
{
	return bonds.at(bIndex);	
}

int TemplateMolecule::addEmptyBindingSite(const char * bSiteName)
{
	return this->addEmptyBindingSite(parentMoleculeType->getBindingSiteIndex(bSiteName));	
}

int TemplateMolecule::addEmptyBindingSite(int bSiteIndex)
{
	this->bSiteIndex.push_back(bSiteIndex);
	bonds.push_back(0);
	hasVisitedBond.push_back(false);
	bSiteIndexOfBond.push_back(-1);
	return (this->bSiteIndex.size()-1);  //return the index that we added this bSiteIndex to
}


void TemplateMolecule::addOccupiedBindingSite(char * bSiteName)
{
	this->sitesThatMustBeOccupied.push_back(parentMoleculeType->getBindingSiteIndex(bSiteName));
}


bool TemplateMolecule::isStateValue(const char * stateName, int stateVal)
{
	int sIndex = parentMoleculeType->getStateIndex(stateName);
	for(unsigned int s=0; s<stateIndex.size(); s++)
	{
			if(stateIndex.at(s)==sIndex)
			{ 
				if(stateValue.at(s)==stateVal)
					return true;
				return false;
			}
	}
	return false;
}

bool TemplateMolecule::isBonded(const char * bSiteName)
{
	int bIndex = parentMoleculeType->getBindingSiteIndex(bSiteName);
	for(unsigned int b=0; b<sitesThatMustBeOccupied.size(); b++)
	{
		if(sitesThatMustBeOccupied.at(b)==bIndex)
			return true;
	}
	for(unsigned int b=0; b<bSiteIndex.size(); b++)
	{
		if(bSiteIndex.at(b)==bIndex)
		{
			if(bonds.at(b)!=NULL)
				return true;
			else
				return false;
		}
	}
	return false;
	
}

void TemplateMolecule::bind(TemplateMolecule *t1, int bSiteIndex1, TemplateMolecule *t2, int bSiteIndex2)
{
	//Find the site of bSiteIndex1 and bSiteIndex2
	int bIndex1 = -1;
	for(unsigned int b1=0; b1<t1->bSiteIndex.size(); b1++)
	{
		if(t1->bSiteIndex.at(b1)==bSiteIndex1) bIndex1 = b1;	
	}
	int bIndex2 = -1;
	for(unsigned int b2=0; b2<t2->bSiteIndex.size(); b2++)
	{
		if(t2->bSiteIndex.at(b2)==bSiteIndex2) bIndex2 = b2;	
	}
	
	//IF we didn't have the bonds created already, create them now
	if(bIndex1==-1) bIndex1 = t1->addEmptyBindingSite(bSiteIndex1);
	if(bIndex2==-1) bIndex2 = t2->addEmptyBindingSite(bSiteIndex2);
	
	//Finally, we can set the bonds
	t1->bonds.at(bIndex1) = t2;
	t1->bSiteIndexOfBond.at(bIndex1) = bIndex2;
	t2->bonds.at(bIndex2) = t1;
	t2->bSiteIndexOfBond.at(bIndex2) = bIndex1;
}

void TemplateMolecule::bind(TemplateMolecule *t1, const char * bSiteName1, TemplateMolecule *t2, const char * bSiteName2)
{
	int bSiteIndex1 = t1->parentMoleculeType->getBindingSiteIndex(bSiteName1);
	int bSiteIndex2 = t2->parentMoleculeType->getBindingSiteIndex(bSiteName2);
	
	bind(t1,bSiteIndex1, t2, bSiteIndex2); 
}





bool TemplateMolecule::compare(Molecule * m)
{
	//if(DEBUG) {
	//	cout<<"Calling Template Molecule compare: "<<endl;
	//	m->printDetails();
	//	this->printDetails();
	//}
	
	
	//First check if we've been here before
	if(matchMolecule!=0)
	{
		if(matchMolecule == m) { return true;	}
		else { clear(); return false; }
	}
	
	//Next, check if we have the same type
	if(m->getMoleculeType()!=this->parentMoleculeType)
	{
		clear();
		return false;
	}
	//Check that states are correct
	for(unsigned int s=0; s<stateIndex.size(); s++)
	{
		if(m->getState(stateIndex.at(s)) != stateValue.at(s))
		{ 
			clear();
			return false; 
		}
	}
	
	for(unsigned int s=0; s<notStateIndex.size(); s++)
	{
		if(m->getState(notStateIndex.at(s)) == notStateValue.at(s))
		{ 
			clear();
			return false; 
		}
	}
	
	
	//Check if the sites that must be occupied by anything are occupied
	for(unsigned int b=0; b<sitesThatMustBeOccupied.size(); b++)
	{
		//cout<<"Checking site that must be occupied: "<< sitesThatMustBeOccupied.at(b) <<endl;
		//If the site is not occupied in the molecule, no match
		if(!m->isBindingSiteBonded(sitesThatMustBeOccupied.at(b)))
		{
			clear();
			return false;
		}
	}
	
	
	
	//We have matched so far, so set our match
	matchMolecule = m;
	
	//Cycle through the bonds
	for(unsigned int b=0; b<bSiteIndex.size(); b++)
	{
		if(hasVisitedBond.at(b)==true) continue;
		if(bonds.at(b)==0) //template binding site is open, so molecule binding site must be too.
		{
			if( m->isBindingSiteBonded(bSiteIndex.at(b)))
			{
				clear();
				return false;
			}
		}
		else //template binding site has a bond
		{
			if(m->isBindingSiteOpen(bSiteIndex.at(b)))
			{
				clear();
				return false;
			}
			
			//get template that is bound to this binding site
			TemplateMolecule * t2 = this->getBondedTemplateMolecule(b);
			Molecule * m2 = m->getBondedMolecule(bSiteIndex.at(b));
			
			//We have to remember to check that it was the right bond site on the other molecule
			//too.  This means that the bond site in m2 that m is connected to must be the same
			//bond site in t2 that t1 is connected to.  If not, then we must say false
			if(m->getBsiteIndexOfBond(bSiteIndex.at(b)) != t2->bSiteIndex.at(bSiteIndexOfBond.at(b)))
			{
				clear();
				return false;
			}
			
			//tell t2 we have visited this bond before, now that we are sure it is correct
			t2->setHasVisited(bSiteIndexOfBond.at(b));
			
			//remember that we visited through this bond in this template, in case we get to
			//this molecule again
			this->setHasVisited(b); 
			
			bool goodMatch = t2->compare(m2);
			if(!goodMatch)
			{
				clear();
				return false;
			}
		}		
	}
	
	// we have a match!  so clear and return
	//cout<<"Match!"<<endl;
	clear();
	return true;
}


void TemplateMolecule::addTemplateMapping(TemplateMapping *tm)
{
	tMappings.push_back(tm);
}

bool TemplateMolecule::compare(Molecule * m, MappingSet *mappingSet)
{	//First check if we've been here before
	if(matchMolecule!=0)
	{
		if(matchMolecule == m) { return true;	}
		else { clear(); return false; }
	}
	
	//Next, check if we have the same type
	if(m->getMoleculeType()!=this->parentMoleculeType)
	{
		clear();
		return false;
	}
	//Check that states are correct
	for(unsigned int s=0; s<stateIndex.size(); s++)
	{
		if(m->getState(stateIndex.at(s)) != stateValue.at(s))
		{ 
			clear();
			return false; 
		}
	}
	
	for(unsigned int s=0; s<notStateIndex.size(); s++)
	{
		if(m->getState(notStateIndex.at(s)) == notStateValue.at(s))
		{ 
			clear();
			return false; 
		}
	}
	
	
	//Check if the sites that must be occupied by anything are occupied
	for(unsigned int b=0; b<sitesThatMustBeOccupied.size(); b++)
	{
		//cout<<"Checking site that must be occupied: "<< sitesThatMustBeOccupied.at(b) <<endl;
		//If the site is not occupied in the molecule, no match
		if(!m->isBindingSiteBonded(sitesThatMustBeOccupied.at(b)))
		{
			clear();
			return false;
		}
	}
	
	
	
	//We have matched so far, so set our match
	matchMolecule = m;
	
	//Cycle through the bonds
	for(unsigned int b=0; b<bSiteIndex.size(); b++)
	{
		if(hasVisitedBond.at(b)==true) continue;
		if(bonds.at(b)==0) //template binding site is open, so molecule binding site must be too.
		{
			if( m->isBindingSiteBonded(bSiteIndex.at(b)))
			{
				clear();
				return false;
			}
		}
		else //template binding site has a bond
		{
			if(m->isBindingSiteOpen(bSiteIndex.at(b)))
			{
				clear();
				return false;
			}
			
			//get template that is bound to this binding site
			TemplateMolecule * t2 = this->getBondedTemplateMolecule(b);
			Molecule * m2 = m->getBondedMolecule(bSiteIndex.at(b));
			
			//We have to remember to check that it was the right bond site on the other molecule
			//too.  This means that the bond site in m2 that m is connected to must be the same
			//bond site in t2 that t1 is connected to.  If not, then we must say false
			if(m->getBsiteIndexOfBond(bSiteIndex.at(b)) != t2->bSiteIndex.at(bSiteIndexOfBond.at(b)))
			{
				clear();
				return false;
			}
			
			//tell t2 we have visited this bond before, now that we are sure it is correct
			t2->setHasVisited(bSiteIndexOfBond.at(b));
			
			//remember that we visited through this bond in this template, in case we get to
			//this molecule again
			this->setHasVisited(b); 
			
			bool goodMatch = t2->compare(m2, mappingSet);
			if(!goodMatch)
			{
				clear();
				return false;
			}
		}		
	}
	clear();
	
	
	//If we got here, we are going to return true, so create the new mappings we will need
	for(tMapIter = tMappings.begin(); tMapIter != tMappings.end(); tMapIter++ )
		mappingSet->add( (*tMapIter)->createNewMapping(m) );
	
	return true;
}


void TemplateMolecule::printDetails() const
{
	cout<<"~~ Template Molecule of type: " << parentMoleculeType->getName() << endl;
	cout<<"      constraints on states: ";
	if(stateIndex.size()==0) cout<<"none.";
	for(unsigned int s=0; s<stateIndex.size(); s++)
	{
		cout<< parentMoleculeType->getStateName(stateIndex.at(s)) <<"=";
		cout<< stateValue.at(s) << " ";
	}
	cout<<endl<<"      constraints on bonds: ";
	if(bSiteIndex.size()==0) cout<<"none.";
	for(unsigned int b=0; b<bSiteIndex.size(); b++)
	{
		cout<< parentMoleculeType->getBindingSiteName(bSiteIndex.at(b)) <<"=";
		if(bonds.at(b)==0) cout<<"empty ";
		else cout<<"full "; 
	}
	cout<<endl<<"      has match molecule: ";
	if(matchMolecule==0) cout<< "no";
	else cout<<"yes";
	
	cout<<endl<<"      have traversed bond: ";
	if(bSiteIndex.size()==0) cout<<"n/a";
	for(unsigned int b=0; b<bSiteIndex.size(); b++)
	{
		cout<< parentMoleculeType->getBindingSiteName(bSiteIndex.at(b)) <<"=";
		if(hasVisitedBond.at(b)==0) cout<<"no ";
		else cout<<"yes "; 
	}
	
	
	
	cout<<endl<<endl;
}



int TemplateMolecule::getTemplateBsiteIndexFromMoleculeBsiteIndex(int molBsiteIndex)
{
	for(unsigned int b=0; b<bSiteIndex.size(); b++)
		if(bSiteIndex.at(b)==molBsiteIndex)
			return b;
	return -1;
}


