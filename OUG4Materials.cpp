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
    SetC7LYCMaterial_99_9();
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
    C6LYC_95 = new G4Material(name,density,ncomponents);
    C6LYC_95->AddElementByNumberOfAtoms(elCs,2);
    C6LYC_95->AddElementByNumberOfAtoms(Li6Enh_el, 1);
    C6LYC_95->AddElementByNumberOfAtoms(elY, 1);
    C6LYC_95->AddElementByNumberOfAtoms(elCl, 6);

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
    C7LYC_99 = new G4Material(name,density,ncomponents);
    C7LYC_99->AddElementByNumberOfAtoms(elCs,2);
    C7LYC_99->AddElementByNumberOfAtoms(Li7Enh_el, 1);
    C7LYC_99->AddElementByNumberOfAtoms(elY, 1);
    C7LYC_99->AddElementByNumberOfAtoms(elCl, 6);

    return;
}

// Set the C7LYC Material with 99.9% Lithium-7
// It is likely the Lithium-6 abundance is below even %1 for the 75 mm x 10 mm detector. This
// allows tests of that material. Experiments suggest that the content must
// be well below 1%, despite the indications on the data sheet.
void OUG4Materials::SetC7LYCMaterial_99_9()
{
    // Define some base properties of the new material
    G4String name = "C7LYC_99_9";
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
    Li7Enh_el->AddIsotope(Li6_i, .1 * perCent);
    Li7Enh_el->AddIsotope(Li7_i, 99.9 * perCent);

    // Get the other elements from constructing the detector from the geant4 database. All other elements used in construction of the detector are of natural abundance.
    G4Element* elCl = NistManager->FindOrBuildElement(17);
    G4Element* elY = NistManager->FindOrBuildElement(39);
    G4Element* elCs = NistManager->FindOrBuildElement(55);

    // Define the clyc molecule and add the components to it
    C7LYC_99_9 = new G4Material(name,density,ncomponents);
    C7LYC_99_9->AddElementByNumberOfAtoms(elCs,2);
    C7LYC_99_9->AddElementByNumberOfAtoms(Li7Enh_el, 1);
    C7LYC_99_9->AddElementByNumberOfAtoms(elY, 1);
    C7LYC_99_9->AddElementByNumberOfAtoms(elCl, 6);

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
    HAVAR = new G4Material(name,density,ncomponents);
    HAVAR->AddElement(elCo, 42*perCent);
    HAVAR->AddElement(elCr, 19.5*perCent);
    HAVAR->AddElement(elNi, 12.7*perCent);
    HAVAR->AddElement(elW, 2.7*perCent);
    HAVAR->AddElement(elMo, 2.2*perCent);
    HAVAR->AddElement(elMn, 1.6*perCent);
    HAVAR->AddElement(elC, 0.2*perCent);
    HAVAR->AddElement(elFe, 19.1*perCent);

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
    MuMetal_UNS14080 = new G4Material(name,density,ncomponents);
    MuMetal_UNS14080->AddElement(elNi, 80*perCent);
    MuMetal_UNS14080->AddElement(elMo, 6*perCent);
    MuMetal_UNS14080->AddElement(elFe, 14*perCent);

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
    Quartz = new G4Material(name,density,ncomponents=2);
    Quartz->AddElementByNumberOfAtoms(elSi,1);
    Quartz->AddElementByNumberOfAtoms(elO,2);

    return;
}

// Set the Be9 target material based on the specs from Standford Advanced Materials
void OUG4Materials::SetSAMBe9TargetMaterial()
{
    // Define Be2C
    // Get the elemental components of the material
    G4Element* elBe = NistManager->FindOrBuildElement(4);
    G4Element* elC = NistManager->FindOrBuildElement(6);
    G4Element* elO = NistManager->FindOrBuildElement(8);

    // Define the new material and add the components to it
    G4Material *Be2C = new G4Material(name="Be2C",1.9*g/cm3,ncomponents=2);
    Be2C->AddElementByNumberOfAtoms(elBe,2);
    Be2C->AddElementByNumberOfAtoms(elC,1);
    
    // Define some base properties of the new material
    G4String name = "SAM_Be9";
    G4double density = 1.845 * g/cm3;
    G4int ncomponents = 11;

    G4Element* elAl = NistManager->FindOrBuildElement(13);
    G4Element* elCu = NistManager->FindOrBuildElement(29);
    G4Element* elCr = NistManager->FindOrBuildElement(24);
    G4Element* elFe = NistManager->FindOrBuildElement(26);
    G4Element* elMn = NistManager->FindOrBuildElement(25);
    G4Element* elNi = NistManager->FindOrBuildElement(28);
    G4Element* elSi = NistManager->FindOrBuildElement(14);

    SAMBe9 = new G4Material(name,density,ncomponents);
    SAMBe9->AddElementByMassFraction(elBe,98.25*perCent);
    // Impurities
    SAMBe9->AddElementByMassFraction(elAl,0.05*perCent);
    SAMBe9->AddElementByMassFraction(elCu,0.02*perCent);
    SAMBe9->AddElementByMassFraction(elCr,0.02*perCent);
    SAMBe9->AddElementByMassFraction(elFe,0.13*perCent);
    SAMBe9->AddElementByMassFraction(elMn,0.02*perCent);
    SAMBe9->AddElementByMassFraction(elNi,0.02*perCent);
    SAMBe9->AddElementByMassFraction(elSi,0.06*perCent);
    SAMBe9->AddMaterial(Be2C,0.15*perCent);
    SAMBe9->AddElementByMassFraction(elO,1.28*perCent);

    return;
}
