#include "HcalClosureTest/DataFormat/interface/DijetRespCorrData.h"

#include "TMinuit.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>

ClassImp(DijetRespCorrDatum)
ClassImp(DijetRespCorrData)

DijetRespCorrDatum::DijetRespCorrDatum() {
    fTagEta=fProbeEta=fTagEcalE=fProbeEcalE=0.0;
}

DijetRespCorrDatum::~DijetRespCorrDatum() {}

Double_t DijetRespCorrDatum::GetWeight(void) const
{
    return fWeight;
}

Double_t DijetRespCorrDatum::GetTagEta(void) const
{
    return fTagEta;
}

Double_t DijetRespCorrDatum::GetTagPhi(void) const
{
    return fTagPhi;
}

Double_t DijetRespCorrDatum::GetTagHcalE(Int_t ieta)
{
    Double_t v=fTagHcalE[ieta];
    return v;
}

void DijetRespCorrDatum::GetTagHcalE(std::map<Int_t, Double_t>& m) const
{
    m=fTagHcalE;
    return;
}

Double_t DijetRespCorrDatum::GetTagEcalE(void) const
{
    return fTagEcalE;
}

Double_t DijetRespCorrDatum::GetProbeEta(void) const
{
    return fProbeEta;
}

Double_t DijetRespCorrDatum::GetProbePhi(void) const
{
    return fProbePhi;
}

Double_t DijetRespCorrDatum::GetProbeHcalE(Int_t ieta)
{
    Double_t v=fProbeHcalE[ieta];
    return v;
}

void DijetRespCorrDatum::GetProbeHcalE(std::map<Int_t, Double_t>& m) const
{
    m=fProbeHcalE;
    return;
}

Double_t DijetRespCorrDatum::GetProbeEcalE(void) const
{
    return fProbeEcalE;
}

Double_t DijetRespCorrDatum::GetThirdJetPx(void) const
{
    return fThirdJetPx;
}

Double_t DijetRespCorrDatum::GetThirdJetPy(void) const
{
    return fThirdJetPy;
}

Int_t DijetRespCorrDatum::GetCandTrackN(void) const
{
    return fCandTrackN;
}

void DijetRespCorrDatum::SetWeight(Double_t v)
{
    fWeight = v;
    return;
}

void DijetRespCorrDatum::SetTagEta(Double_t v)
{
    fTagEta = v;
    return;
}

void DijetRespCorrDatum::SetTagPhi(Double_t v)
{
    fTagPhi = v;
    return;
}

void DijetRespCorrDatum::SetTagHcalE(Double_t v, Int_t ieta)
{
    assert(ieta <= MAXIETA && ieta >= -MAXIETA && ieta != 0);
    fTagHcalE[ieta] = v;
    return;
}

void DijetRespCorrDatum::AddTagHcalE(Double_t v, Int_t ieta)
{
    assert(ieta <= MAXIETA && ieta >= -MAXIETA && ieta != 0);
    fTagHcalE[ieta] += v;
    return;
}

void DijetRespCorrDatum::SetTagEcalE(Double_t v)
{
    fTagEcalE = v;
    return;
}

void DijetRespCorrDatum::SetProbeEta(Double_t v)
{
    fProbeEta = v;
    return;
}

void DijetRespCorrDatum::SetProbePhi(Double_t v)
{
    fProbePhi = v;
    return;
}

void DijetRespCorrDatum::SetProbeHcalE(Double_t v, Int_t ieta)
{
    assert(ieta <= MAXIETA && ieta >= -MAXIETA && ieta != 0);
    fProbeHcalE[ieta] = v;
    return;
}

void DijetRespCorrDatum::AddProbeHcalE(Double_t v, Int_t ieta)
{
    assert(ieta <= MAXIETA && ieta >= -MAXIETA && ieta != 0);
    fProbeHcalE[ieta] += v;
    return;
}

void DijetRespCorrDatum::SetProbeEcalE(Double_t v)
{
    fProbeEcalE = v;
    return;
}

void DijetRespCorrDatum::SetThirdJetPx(Double_t v)
{
    fThirdJetPx = v;
    return;
}

void DijetRespCorrDatum::SetThirdJetPy(Double_t v)
{
    fThirdJetPy = v;
    return;
}

void DijetRespCorrDatum::SetCandTrackN(Int_t v)
{
    fCandTrackN = v;
    return;
}

void DijetRespCorrDatum::AddCandTrackP(Double_t v)
{
    fCandTrackP.push_back(v);
    return;
}

void DijetRespCorrDatum::AddCandTrackEcalE(Double_t v)
{
    fCandTrackEcalE.push_back(v);
    return;
}

void DijetRespCorrDatum::AddCandTrackHcalE(std::map<Int_t, Double_t> v)
{
  fCandTrackHcalE.push_back(v);
  return;
}

void DijetRespCorrDatum::GetTagEnergies(const TArrayD& respcorr, Double_t& ecal,
					Double_t& hcal, Double_t& hf) const
{
    ecal=GetTagEcalE();
    hcal=0.0;
    hf=0.0;

    std::map<Int_t,Double_t> tagmap;
    GetTagHcalE(tagmap);
    for (std::map<Int_t, Double_t>::const_iterator mapit=tagmap.begin();
	 mapit!=tagmap.end(); ++mapit) {
	int ieta = mapit->first;
	double energy = mapit->second;
	int index = ieta + MAXIETA;
	if (std::abs(ieta) > 29)
	    hf += respcorr[index]*energy;
	else
	    hcal += respcorr[index]*energy;
    }
    return;
}

void DijetRespCorrDatum::GetProbeEnergies(const TArrayD& respcorr,
					  Double_t& ecal, Double_t& hcal,
					  Double_t& hf) const
{
    // calculate the ecal, hcal, and HF energy
    // scale the hcal and hf energy by the response corrections
    ecal = GetProbeEcalE();
    hcal = 0.0;
    hf = 0.0;

    std::map<Int_t,Double_t> probemap;
    GetProbeHcalE(probemap);
    for (std::map<Int_t, Double_t>::const_iterator mapit=probemap.begin();
	 mapit!=probemap.end(); ++mapit) {
	int ieta = mapit->first;
	double energy = mapit->second;
	int index = ieta + MAXIETA;
	if(std::abs(ieta) > 29)
	    hf += respcorr[index]*energy;
	else
	    hcal += respcorr[index]*energy;
    }
    return;
}

void DijetRespCorrDatum::GetTrackVariables(const TArrayD& respcorr,
					   const Int_t index_,
					   Double_t& TrackP_, Double_t& EcalE_,
					   Double_t& HcalE_) const
{
    TrackP_ = fCandTrackP[index_];
    EcalE_ = fCandTrackEcalE[index_];

    std::map<Int_t,Double_t> candmap = fCandTrackHcalE[index_];
    for (std::map<Int_t, Double_t>::const_iterator mapit=candmap.begin();
	 mapit!=candmap.end(); ++mapit) {
	int ieta=mapit->first;
	double energy=mapit->second;
	int index=ieta+MAXIETA;
	HcalE_ += respcorr[index]*energy;
    }
    return;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

DijetRespCorrData::DijetRespCorrData()
{
    fData.clear();
    fPrintLevel=5;
    fParStep=0.10;
    fParMin=0.0;
    fParMax=0.0;
    fEcalRes=0.07;
    fHcalRes=1.15;
    fHfRes=1.35;

    fDoCandTrackEnergyDiff=false;
}

DijetRespCorrData::~DijetRespCorrData() {}

void DijetRespCorrData::push_back(const DijetRespCorrDatum& d)
{
    fData.push_back(d);
    return;
}

const DijetRespCorrDatum& DijetRespCorrData::GetAt(Int_t i) const
{
    return fData[i];
}

Int_t DijetRespCorrData::GetSize(void) const
{
    return fData.size();
}

Double_t DijetRespCorrData::GetLikelihoodDistance(const TArrayD& respcorr) const
{
    Double_t total=0.0;

    if (GetDoCandTrackEnergyDiff()) {
	// loop over each jet pair
	for (std::vector<DijetRespCorrDatum>::const_iterator it=fData.begin();
	     it!=fData.end(); ++it) {

	    // calculate the balance and resolution for each jet pair
	    Double_t B, dB;
	    GetBalance(*it, respcorr, B, dB);

	    // this is the total likelihood
	    total += 0.5*(std::log(dB*dB)+B*B/dB/dB);
	    for (Int_t iCandTrack=0; iCandTrack<(*it).GetCandTrackN();
		 ++iCandTrack){
		// Calculate the difference in energy between rechits and tracks
		Double_t Ediff, dEdiff;
		GetTrackEnergyDiff(*it, iCandTrack, respcorr, Ediff, dEdiff);
		total += 0.5*(std::log(dEdiff*dEdiff)
			      + Ediff*Ediff/dEdiff/dEdiff);
	    }
	}
    } else {
	// loop over each jet pair
	for (std::vector<DijetRespCorrDatum>::const_iterator it=fData.begin();
	     it!=fData.end(); ++it) {

	    // calculate the balance and resolution for each jet pair
	    Double_t B, dB;
	    GetBalance(*it, respcorr, B, dB);

	    // this is the total likelihood
	    total += 0.5*(std::log(dB*dB)+B*B/dB/dB);
	}
    }
    return total;
}

TH1D* DijetRespCorrData::doFit(const char* name, const char* title)
{
    TArrayD respcorr, respcorre;
    doFit(respcorr, respcorre);
    TH1D* h = new TH1D(name, title, NUMTOWERS, -MAXIETA - 0.5, MAXIETA + 0.5);
    for (int i=1; i<=NUMTOWERS; ++i) {
	h->SetBinContent(i, respcorr[i-1]);
	h->SetBinError(i, respcorre[i-1]);
    }

    return h;
}

void DijetRespCorrData::doFit(TArrayD& respcorr, TArrayD& respcorre)
{
    // setup the initial response corrections
    const int maxIetaFixed = 1;//20;
    Double_t array[NUMTOWERS] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

    TArrayD respCorrInit;
    respCorrInit.Set(NUMTOWERS, array);

    // set the number of parameters to be the number of towers
    TMinuit *gMinuit = new TMinuit(NUMTOWERS);
    gMinuit->SetPrintLevel(fPrintLevel);
    //std::cout << "========================= " << gMinuit->GetMaxIterations() << std::endl;
    //gMinuit->SetMaxIterations(1000);
    gMinuit->SetErrorDef(0.5); // for a log likelihood
    gMinuit->SetFCN(FCN);
    gMinuit->SetObjectFit(this);

    // define the parameters
    for (int i=0; i<respCorrInit.GetSize(); ++i) {
	int ieta = -MAXIETA + i;
	std::ostringstream oss;
	oss << "Tower ieta: " << ieta;
	gMinuit->DefineParameter(i, oss.str().c_str(), respCorrInit[i],
				 fParStep, fParMin, fParMax);
	if(ieta>=-maxIetaFixed && ieta<=maxIetaFixed) gMinuit->FixParameter(i);

	// override the HF
	/*if(ieta<=-30 || ieta>=30) {
	  gMinuit->DefineParameter(i, oss.str().c_str(), 1.0, fParStep, fParMin, fParMax);
	  //gMinuit->DefineParameter(i, oss.str().c_str(), 1.3, fParStep, fParMin, fParMax);
	  gMinuit->FixParameter(i);
	  }*/
    }

    //gMinuit->Command("SET STR 2");

    // Minimize
    gMinuit->Migrad();

    // get the results
    TArrayD results(NUMTOWERS);
    TArrayD errors(NUMTOWERS);
    for (int i=0; i<results.GetSize(); ++i) {
	Double_t val, error;
	gMinuit->GetParameter(i, val, error);
	results[i]=val;
	errors[i]=error;
    }
    respcorr=results;
    respcorre=errors;

    return;
}

void DijetRespCorrData::GetBalance(const DijetRespCorrDatum& datum,
				   const TArrayD& respcorr, Double_t& balance_,
				   Double_t& resolution_) const
{
    Double_t te, th, thf;
    Double_t pe, ph, phf;
    datum.GetTagEnergies(respcorr, te, th, thf);
    datum.GetProbeEnergies(respcorr, pe, ph, phf);

    // calculate the resolution and balance in E_T, not E
    Double_t tet=(te+th+thf)/std::cosh(datum.GetTagEta());
    Double_t pet=(pe+ph+phf)/std::cosh(datum.GetProbeEta());

    // correct the tag/probe E_T's for the "third jet"
    Double_t tpx = tet*std::cos(datum.GetTagPhi());
    Double_t tpy = tet*std::sin(datum.GetTagPhi());
    Double_t ppx = pet*std::cos(datum.GetProbePhi());
    Double_t ppy = pet*std::sin(datum.GetProbePhi());

    tpx += 0.5*datum.GetThirdJetPx();
    tpy += 0.5*datum.GetThirdJetPy();
    ppx += 0.5*datum.GetThirdJetPx();
    ppy += 0.5*datum.GetThirdJetPy();

    Double_t tetcorr = std::sqrt(tpx*tpx + tpy*tpy);
    Double_t petcorr = std::sqrt(ppx*ppx + ppy*ppy);

    balance_ = 2.0*(tetcorr-petcorr)/(tetcorr+petcorr);
    resolution_ = 0.237/sqrt(datum.GetWeight()); //0.035
    return;
}

void DijetRespCorrData::GetTrackEnergyDiff(const DijetRespCorrDatum& datum,
					   const Int_t index,
					   const TArrayD& respcorr,
					   Double_t& Ediff_,
					   Double_t& dEdiff_) const
{
    Double_t TrackP, EcalE, HcalE;
    datum.GetTrackVariables(respcorr, index, TrackP, EcalE, HcalE);

                   // sqrt(p^2 + m_pion^2)
    Double_t TrackE = sqrt(TrackP*TrackP + 0.019479835145232396);

    Ediff_ = fabs(TrackE - EcalE - HcalE);
    dEdiff_ = 1.0;
    return;
}

void DijetRespCorrData::FCN(Int_t &npar, Double_t*, Double_t &f, Double_t *par,
			    Int_t)
{
    // get the relevant data
    const DijetRespCorrData* data =
	dynamic_cast<const DijetRespCorrData*>(gMinuit->GetObjectFit());
    TArrayD respcorr;
    respcorr.Set(NUMTOWERS, par);
    f = data->GetLikelihoodDistance(respcorr);

    return;
}
