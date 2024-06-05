#include "OUG4Materials.hpp"
#include "G4NistManager.hh"
#include "G4Material.hh"

using namespace CLHEP;

// Constructors

// Default constructor. Generally shouldn't be used
OUG4Materials::OUG4Materials()
{

}

// Typical constructor to use
OUG4Materials::OUG4Materials(G4NistManager* thenist)
{
    NistManager = thenist;

    SetMaterials();
}

// Destructor
OUG4Materials::~OUG4Materials()
{

}

// Set the G4NistManager
void OUG4Materials::SetNistManager(G4NistManager* thenist)
{
    NistManager = thenist;
    return;
}

// Set the materials
void OUG4Materials::SetMaterials()
{
    SetC6LYCMaterial_95();
    SetC7LYCMaterial_99();
    SetHAVARMaterial();
    Set_MuMetal_UNS14080Material();
    SetQuartzMaterial();

    return;
}

// Set the C6LYC Material with >95% Lithium-6
void OUG4Materials::SetC6LYCMaterial_95()
{
    // Define some base properties of the new material
    G4String name = "C6LYC_95";
    G4double density = 3.31 * g/cm3;
    G4int ncomponents = 4;

    // Define the enriched Li6 element
    G4Element* Li6Enh_el = new G4Element("Li6Enhanced","Li6Enh" ,2);

    // Get the natural abundance litium from the geant4 database
    G4Element* Li_i = NistManager->FindOrBuildElement("Li",true);
    
    // Get the Li6 and Li7 isotopes from the geant4 database; must use const_cast<G4Isotope *> () to successfully use in construction of enriched element.
    
    // Get Li6
    G4Isotope* Li6_i = const_cast<G4Isotope *> (Li_i->GetIsotope(0));
    
    // Get Li7 
    G4Isotope* Li7_i = const_cast<G4Isotope *> (Li_i->GetIsotope(1));

    // Add Li6 and Li7 to the enriched element
    Li6Enh_el->AddIsotope(Li6_i, 95 * perCent);
    Li6Enh_el->AddIsotope(Li7_i, 5 * perCent);

    // Get the other elements from constructing the detector from the geant4 database. All other elements used in construction of the detector are of natural abundance.
    G4Element* elCl = NistManager->FindOrBuildElement(17);
    G4Element* elY = NistManager->FindOrBuildElement(39);
    G4Element* elCs = NistManager->FindOrBuildElement(55);

    // Define the CLYC molecule
    G4Material* CLYC_molecule = new G4Material(name,density,ncomponents);
    CLYC_molecule->AddElement(elCs, 20*perCent);
    CLYC_molecule->AddElement(Li6Enh_el, 10*perCent);
    CLYC_molecule->AddElement(elY, 10*perCent);
    CLYC_molecule->AddElement(elCl, 60*perCent);

    C6LYC_95 = CLYC_molecule;

    return;

}

// Set the C7LYC Material with >99% Lithium-7
void OUG4Materials::SetC7LYCMaterial_99()
{
    // Define some base properties of the new material
    G4String name = "C7LYC_99";
    G4double density = 3.31 * g/cm3;
    G4int ncomponents = 4;

    // Define the enriched Li6 element
    G4Element* Li7Enh_el = new G4Element("Li7Enhanced","Li7Enh" ,2);

    // Get the natural abundance litium from the geant4 database
    G4Element* Li_i = NistManager->FindOrBuildElement("Li",true);
    
    // Get the Li6 and Li7 isotopes from the geant4 database; must use const_cast<G4Isotope *> () to successfully use in construction of enriched element.
    
    // Get Li6
    G4Isotope* Li6_i = const_cast<G4Isotope *> (Li_i->GetIsotope(0));
    
    // Get Li7 
    G4Isotope* Li7_i = const_cast<G4Isotope *> (Li_i->GetIsotope(1));

    // Add Li6 and Li7 to the enriched element
    Li7Enh_el->AddIsotope(Li6_i, 1 * perCent);
    Li7Enh_el->AddIsotope(Li7_i, 99 * perCent);

    // Get the other elements from constructing the detector from the geant4 database. All other elements used in construction of the detector are of natural abundance.
    G4Element* elCl = NistManager->FindOrBuildElement(17);
    G4Element* elY = NistManager->FindOrBuildElement(39);
    G4Element* elCs = NistManager->FindOrBuildElement(55);

    // Define the clyc molecule and add the components to it
    G4Material* CLYC_molecule = new G4Material(name,density,ncomponents);
    CLYC_molecule->AddElement(elCs, 20*perCent);
    CLYC_molecule->AddElement(Li7Enh_el, 10*perCent);
    CLYC_molecule->AddElement(elY, 10*perCent);
    CLYC_molecule->AddElement(elCl, 60*perCent);

    C7LYC_99 = CLYC_molecule;

    return;
}

// Set the HAVAR material (used for gas cell windows)
void OUG4Materials::SetHAVARMaterial()
{
    // Define some base properties of the new material
    G4String name = "HAVAR";
    G4double density = 8.3 * g/cm3;
    G4int ncomponents = 8;

    // Get the elemental components of the material
    G4Element* elCo = NistManager->FindOrBuildElement(27);
    G4Element* elCr = NistManager->FindOrBuildElement(24);
    G4Element* elNi = NistManager->FindOrBuildElement(28);
    G4Element* elW = NistManager->FindOrBuildElement(74);
    G4Element* elMo = NistManager->FindOrBuildElement(42);
    G4Element* elMn = NistManager->FindOrBuildElement(25);
    G4Element* elC = NistManager->FindOrBuildElement(6);
    G4Element* elFe = NistManager->FindOrBuildElement(26);

    // Define the new material and add the components to it
    G4Material* HAVAR_alloy = new G4Material(name,density,ncomponents);
    HAVAR_alloy->AddElement(elCo, 42*perCent);
    HAVAR_alloy->AddElement(elCr, 19.5*perCent);
    HAVAR_alloy->AddElement(elNi, 12.7*perCent);
    HAVAR_alloy->AddElement(elW, 2.7*perCent);
    HAVAR_alloy->AddElement(elMo, 2.2*perCent);
    HAVAR_alloy->AddElement(elMn, 1.6*perCent);
    HAVAR_alloy->AddElement(elC, 0.2*perCent);
    HAVAR_alloy->AddElement(elFe, 19.1*perCent);

    HAVAR = HAVAR_alloy;

    return;
}

// Set the MuMetal UNS14080/ASTM A753 Alloy 4 material with 80% Ni, 6% Mo, 14% Fe
void OUG4Materials::Set_MuMetal_UNS14080Material()
{
    // Define some base properties of the new material
    G4String name = "MuMetal_UNS14080";
    G4double density = 8.7 * g/cm3;
    G4int ncomponents = 3;

    // Get the elemental components of the material
    G4Element* elNi = NistManager->FindOrBuildElement(28);
    G4Element* elMo = NistManager->FindOrBuildElement(42);
    G4Element* elFe = NistManager->FindOrBuildElement(26);

    // Define the new material and add the components to it
    G4Material* MuMetal_alloy = new G4Material(name,density,ncomponents);
    MuMetal_alloy->AddElement(elNi, 80*perCent);
    MuMetal_alloy->AddElement(elMo, 6*perCent);
    MuMetal_alloy->AddElement(elFe, 14*perCent);
    
    MuMetal_UNS14080 = MuMetal_alloy;

    return;
}

// Set the Quartz material (typically used in lightguides in inoragic scintillators)
void OUG4Materials::SetQuartzMaterial()
{
    // Define some base properties of the new material
    G4String name = "Quartz";
    G4double density = 2.65 * g/cm3;
    G4int ncomponents = 2;

    // Get the elemental components of the material
    G4Element* elSi = NistManager->FindOrBuildElement(14);
    G4Element* elO = NistManager->FindOrBuildElement(8);

    // Define the new material and add the components to it
    G4Material* Quartz_molecule = new G4Material(name="Quartz",density,ncomponents=2);
    Quartz_molecule->AddElementByNumberOfAtoms(elSi,1);
    Quartz_molecule->AddElementByNumberOfAtoms(elO,2);

    Quartz = Quartz_molecule;

    return;
}
