#include "HcalClosureTest/DataFormat/interface/runPFJetCorr.h"

using namespace std;

int main(int argc, char* argv[])
{
  bool isMC = false;
  float maxDeltaEta_ = 0.5;
  float minJetEt_ = 50.0;
  float maxThirdJetEt_ = 15.0;

  cout << argc << endl;
  if(argc == 5){
    if(atoi(argv[1]) == 1){
      isMC = true;
    }
    else if(atoi(argv[1]) == 0){
      isMC = false;
    }
    else{
      cout << " Usage: runPFJetCorr isMC dEta leadingEt 3rdEt" << endl;
      return 1;
    }
    maxDeltaEta_   = atof(argv[2]);
    minJetEt_      = atof(argv[3]);
    maxThirdJetEt_ = atof(argv[4]);
  }
  else{
    cout << "Not right number of arguments." << endl;
    cout << " Usage: runPFJetCorr isMC dEta leadingEt 3rdEt" << endl;
    return 1;
  }

  TChain* tree = new TChain("pf_dijettree");
  //TString input = "/eos/uscms/store/user/dgsheffi/QCD_Pt-1800_TuneZ2star_8TeV_pythia6/DijetCalibration_dEta-1p5_Et-20_3rdEt-50/b4567834a2ef8afdd36a5bd021a58fe5/tree_*.root";
  //TString input1 = "/uscmst1b_scratch/lpc1/old_scratch/lpceg/yurii/EnSc/HCAL/ProduceDATA/*.root";
  TString input = "/eos/uscms/store/user/dgsheffi/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/DijetCalibration_dEta-1p5_Et-10_3rdEt-50/c1cd07ae23ea077dd65d1e10c6b04785/tree_*.root";
  //TString input2 = "/uscmst1b_scratch/lpc1/old_scratch/lpceg/yurii/EnSc/HCAL/ProduceDATA2/*root";
  cout << "Opening file: " << input << endl;
  tree->Add(input);
  //tree->Add(input1);
  //tree->Add(input2);
  cout << "File opened." << endl;

  //TString output = "/uscms_data/d3/dgsheffi/HCal/corrections/QCD_Pt-1800_dEta-0p5_Et-50_3rdEt-15.root";
  //TString output = "/uscms_data/d1/dgsheffi/HCal/corrections/MultiJet_2012AD_dEta-0p5_Et-50_3rdEt-15_test.root";
  //TString output = "/uscms_data/d1/dgsheffi/HCal/corrections/QCD_Pt-120To170_dEta-0p5_Et-50_3rdEt-15.root";
  int decimal = static_cast<int>(maxDeltaEta_*10)-static_cast<int>(maxDeltaEta_)*10;
  TString output = "QCD_Pt-120To170_dEta-"+to_string(static_cast<int>(maxDeltaEta_))+"p"+to_string(decimal)+"_Et-"+to_string(static_cast<int>(minJetEt_))+"_3rdEt-"+to_string(static_cast<int>(maxThirdJetEt_))+".root";

  DijetRespCorrData data;

  float tjet_pt_, tjet_p_, tjet_E_, tjet_eta_, tjet_phi_, tjet_EMfrac_, tjet_hadEcalEfrac_, tjet_scale_, tjet_area_;
  int tjet_jetID_;
  float tjet_gendr_, tjet_genpt_, tjet_genp_, tjet_genE_;
  float tjet_unkown_E_, tjet_unkown_px_, tjet_unkown_py_, tjet_unkown_pz_, tjet_unkown_EcalE_;
  float tjet_electron_E_, tjet_electron_px_, tjet_electron_py_, tjet_electron_pz_, tjet_electron_EcalE_;
  float tjet_muon_E_, tjet_muon_px_, tjet_muon_py_, tjet_muon_pz_, tjet_muon_EcalE_;
  float tjet_photon_E_, tjet_photon_px_, tjet_photon_py_, tjet_photon_pz_, tjet_photon_EcalE_;
  int tjet_unkown_n_, tjet_electron_n_, tjet_muon_n_, tjet_photon_n_;
  int tjet_had_n_, tjet_cluster_n_;
  vector<float>* tjet_had_E_ = 0;
  vector<float>* tjet_had_px_ = 0;
  vector<float>* tjet_had_py_ = 0;
  vector<float>* tjet_had_pz_ = 0;
  vector<float>* tjet_had_EcalE_ = 0;
  vector<float>* tjet_had_rawHcalE_ = 0;
  vector<float>* tjet_had_emf_ = 0;
  vector<float>* tjet_had_E_mctruth_ = 0;
  vector<int>* tjet_had_id_ = 0;
  vector<int>* tjet_had_candtrackind_ = 0;
  vector<int>* tjet_had_mcpdgId_ = 0;
  vector<int>* tjet_had_ntwrs_ = 0;
  int tjet_ntwrs_;
  vector<int>* tjet_twr_ieta_ = 0;
  vector<int>* tjet_twr_iphi_ = 0;
  vector<int>* tjet_twr_candtrackind_ = 0;
  vector<int>* tjet_twr_hadind_ = 0;
  vector<int>* tjet_twr_elmttype_ = 0;
  vector<int>* tjet_twr_subdet_ = 0;
  vector<float>* tjet_twr_hade_ = 0;
  vector<float>* tjet_twr_frac_ = 0;
  vector<float>* tjet_twr_dR_ = 0;
  vector<int>* tjet_twr_clusterind_ = 0;
  vector<float>* tjet_cluster_eta_ = 0;
  vector<float>* tjet_cluster_phi_ = 0;
  vector<float>* tjet_cluster_dR_ = 0;
  int tjet_ncandtracks_;
  vector<float>* tjet_candtrack_px_ = 0;
  vector<float>* tjet_candtrack_py_ = 0;
  vector<float>* tjet_candtrack_pz_ = 0;
  vector<float>* tjet_candtrack_EcalE_ = 0;
  float pjet_pt_, pjet_p_, pjet_E_, pjet_eta_, pjet_phi_, pjet_EMfrac_, pjet_hadEcalEfrac_, pjet_scale_, pjet_area_;
  int pjet_jetID_;
  float pjet_gendr_, pjet_genpt_, pjet_genp_, pjet_genE_;
  float pjet_unkown_E_, pjet_unkown_px_, pjet_unkown_py_, pjet_unkown_pz_, pjet_unkown_EcalE_;
  float pjet_electron_E_, pjet_electron_px_, pjet_electron_py_, pjet_electron_pz_, pjet_electron_EcalE_;
  float pjet_muon_E_, pjet_muon_px_, pjet_muon_py_, pjet_muon_pz_, pjet_muon_EcalE_;
  float pjet_photon_E_, pjet_photon_px_, pjet_photon_py_, pjet_photon_pz_, pjet_photon_EcalE_;
  int pjet_unkown_n_, pjet_electron_n_, pjet_muon_n_, pjet_photon_n_;
  int pjet_had_n_, pjet_cluster_n_;
  vector<float>* pjet_had_E_ = 0;
  vector<float>* pjet_had_px_ = 0;
  vector<float>* pjet_had_py_ = 0;
  vector<float>* pjet_had_pz_ = 0;
  vector<float>* pjet_had_EcalE_ = 0;
  vector<float>* pjet_had_rawHcalE_ = 0;
  vector<float>* pjet_had_emf_ = 0;
  vector<float>* pjet_had_E_mctruth_ = 0;
  vector<int>* pjet_had_id_ = 0;
  vector<int>* pjet_had_candtrackind_ = 0;
  vector<int>* pjet_had_mcpdgId_ = 0;
  vector<int>* pjet_had_ntwrs_ = 0;
  int pjet_ntwrs_;
  vector<int>* pjet_twr_ieta_ = 0;
  vector<int>* pjet_twr_iphi_ = 0;
  vector<int>* pjet_twr_subdet_ = 0;
  vector<float>* pjet_twr_candtrackind_ = 0;
  vector<float>* pjet_twr_hadind_ = 0;
  vector<float>* pjet_twr_elmttype_ = 0;
  vector<float>* pjet_twr_hade_ = 0;
  vector<float>* pjet_twr_frac_ = 0;
  vector<float>* pjet_twr_dR_ = 0;
  vector<int>* pjet_twr_clusterind_ = 0;
  vector<float>* pjet_cluster_eta_ = 0;
  vector<float>* pjet_cluster_phi_ = 0;
  vector<float>* pjet_cluster_dR_ = 0;
  int pjet_ncandtracks_;
  vector<float>* pjet_candtrack_px_ = 0;
  vector<float>* pjet_candtrack_py_ = 0;
  vector<float>* pjet_candtrack_pz_ = 0;
  vector<float>* pjet_candtrack_EcalE_ = 0;
  float dijet_deta_, dijet_dphi_, dijet_balance_;
  float thirdjet_px_, thirdjet_py_;
  int pf_Run_, pf_Lumi_, pf_Event_, pf_NPV_;
  float weight_;

  tree->SetBranchAddress("tpfjet_E",&tjet_E_);
  tree->SetBranchAddress("tpfjet_pt",&tjet_pt_);
  tree->SetBranchAddress("tpfjet_p",&tjet_p_);
  tree->SetBranchAddress("tpfjet_E",&tjet_E_);
  tree->SetBranchAddress("tpfjet_eta",&tjet_eta_);
  tree->SetBranchAddress("tpfjet_phi",&tjet_phi_);
  tree->SetBranchAddress("tpfjet_EMfrac",&tjet_EMfrac_);
  tree->SetBranchAddress("tpfjet_hadEcalEfrac",&tjet_hadEcalEfrac_);
  tree->SetBranchAddress("tpfjet_scale",&tjet_scale_);
  tree->SetBranchAddress("tpfjet_area",&tjet_area_);
  tree->SetBranchAddress("tpfjet_jetID",&tjet_jetID_);
  if(isMC){
    tree->SetBranchAddress("tpfjet_genpt",&tjet_genpt_);
    tree->SetBranchAddress("tpfjet_genp",&tjet_genp_);
    tree->SetBranchAddress("tpfjet_genE",&tjet_genE_);
    tree->SetBranchAddress("tpfjet_gendr",&tjet_gendr_);
  }
  tree->SetBranchAddress("tpfjet_unkown_E",&tjet_unkown_E_);
  tree->SetBranchAddress("tpfjet_electron_E",&tjet_electron_E_);
  tree->SetBranchAddress("tpfjet_muon_E",&tjet_muon_E_);
  tree->SetBranchAddress("tpfjet_photon_E",&tjet_photon_E_);
  tree->SetBranchAddress("tpfjet_unkown_px",&tjet_unkown_px_);
  tree->SetBranchAddress("tpfjet_electron_px",&tjet_electron_px_);
  tree->SetBranchAddress("tpfjet_muon_px",&tjet_muon_px_);
  tree->SetBranchAddress("tpfjet_photon_px",&tjet_photon_px_);
  tree->SetBranchAddress("tpfjet_unkown_py",&tjet_unkown_py_);
  tree->SetBranchAddress("tpfjet_electron_py",&tjet_electron_py_);
  tree->SetBranchAddress("tpfjet_muon_py",&tjet_muon_py_);
  tree->SetBranchAddress("tpfjet_photon_py",&tjet_photon_py_);
  tree->SetBranchAddress("tpfjet_unkown_pz",&tjet_unkown_pz_);
  tree->SetBranchAddress("tpfjet_electron_pz",&tjet_electron_pz_);
  tree->SetBranchAddress("tpfjet_muon_pz",&tjet_muon_pz_);
  tree->SetBranchAddress("tpfjet_photon_pz",&tjet_photon_pz_);
  tree->SetBranchAddress("tpfjet_unkown_EcalE",&tjet_unkown_EcalE_);
  tree->SetBranchAddress("tpfjet_electron_EcalE",&tjet_electron_EcalE_);
  tree->SetBranchAddress("tpfjet_muon_EcalE",&tjet_muon_EcalE_);
  tree->SetBranchAddress("tpfjet_photon_EcalE",&tjet_photon_EcalE_);
  tree->SetBranchAddress("tpfjet_unkown_n",&tjet_unkown_n_);
  tree->SetBranchAddress("tpfjet_electron_n",&tjet_electron_n_);
  tree->SetBranchAddress("tpfjet_muon_n",&tjet_muon_n_);
  tree->SetBranchAddress("tpfjet_photon_n",&tjet_photon_n_);
  tree->SetBranchAddress("tpfjet_had_n",&tjet_had_n_);
  tree->SetBranchAddress("tpfjet_had_E",&tjet_had_E_);
  tree->SetBranchAddress("tpfjet_had_px",&tjet_had_px_);
  tree->SetBranchAddress("tpfjet_had_py",&tjet_had_py_);
  tree->SetBranchAddress("tpfjet_had_pz",&tjet_had_pz_);
  tree->SetBranchAddress("tpfjet_had_EcalE",&tjet_had_EcalE_);
  tree->SetBranchAddress("tpfjet_had_rawHcalE",&tjet_had_rawHcalE_);
  tree->SetBranchAddress("tpfjet_had_emf",&tjet_had_emf_);
  tree->SetBranchAddress("tpfjet_had_id",&tjet_had_id_);
  tree->SetBranchAddress("tpfjet_had_candtrackind",&tjet_had_candtrackind_);
  if(isMC){
    tree->SetBranchAddress("tpfjet_had_E_mctruth",&tjet_had_E_mctruth_);
    tree->SetBranchAddress("tpfjet_had_mcpdgId",&tjet_had_mcpdgId_);
  }
  tree->SetBranchAddress("tpfjet_had_ntwrs",&tjet_had_ntwrs_);
  tree->SetBranchAddress("tpfjet_ntwrs",&tjet_ntwrs_);
  tree->SetBranchAddress("tpfjet_twr_ieta",&tjet_twr_ieta_);
  tree->SetBranchAddress("tpfjet_twr_iphi",&tjet_twr_iphi_);
  tree->SetBranchAddress("tpfjet_twr_hade",&tjet_twr_hade_);
  tree->SetBranchAddress("tpfjet_twr_frac",&tjet_twr_frac_);
  tree->SetBranchAddress("tpfjet_twr_candtrackind",&tjet_twr_candtrackind_);
  tree->SetBranchAddress("tpfjet_twr_hadind",&tjet_twr_hadind_);
  tree->SetBranchAddress("tpfjet_twr_elmttype",&tjet_twr_elmttype_);
  tree->SetBranchAddress("tpfjet_twr_dR",&tjet_twr_dR_);
  tree->SetBranchAddress("tpfjet_twr_clusterind",&tjet_twr_clusterind_);
  tree->SetBranchAddress("tpfjet_cluster_n",&tjet_cluster_n_);
  tree->SetBranchAddress("tpfjet_cluster_eta",&tjet_cluster_eta_);
  tree->SetBranchAddress("tpfjet_cluster_phi",&tjet_cluster_phi_);
  tree->SetBranchAddress("tpfjet_cluster_dR",&tjet_cluster_dR_);
  tree->SetBranchAddress("tpfjet_twr_subdet",&tjet_twr_subdet_);
  tree->SetBranchAddress("tpfjet_ncandtracks",&tjet_ncandtracks_);
  tree->SetBranchAddress("tpfjet_candtrack_px",&tjet_candtrack_px_);
  tree->SetBranchAddress("tpfjet_candtrack_py",&tjet_candtrack_py_);
  tree->SetBranchAddress("tpfjet_candtrack_pz",&tjet_candtrack_pz_);
  tree->SetBranchAddress("tpfjet_candtrack_EcalE",&tjet_candtrack_EcalE_);
  tree->SetBranchAddress("ppfjet_pt",&pjet_pt_);
  tree->SetBranchAddress("ppfjet_p",&pjet_p_);
  tree->SetBranchAddress("ppfjet_E",&pjet_E_);
  tree->SetBranchAddress("ppfjet_eta",&pjet_eta_);
  tree->SetBranchAddress("ppfjet_phi",&pjet_phi_);
  tree->SetBranchAddress("ppfjet_EMfrac",&pjet_EMfrac_);
  tree->SetBranchAddress("ppfjet_hadEcalEfrac",&pjet_hadEcalEfrac_);
  tree->SetBranchAddress("ppfjet_scale",&pjet_scale_);
  tree->SetBranchAddress("ppfjet_area",&pjet_area_);
  tree->SetBranchAddress("ppfjet_jetID",&pjet_jetID_);
  if(isMC){
    tree->SetBranchAddress("ppfjet_genpt",&pjet_genpt_);
    tree->SetBranchAddress("ppfjet_genp",&pjet_genp_);
    tree->SetBranchAddress("ppfjet_genE",&pjet_genE_);
    tree->SetBranchAddress("ppfjet_gendr",&pjet_gendr_);
  }
  tree->SetBranchAddress("ppfjet_unkown_E",&pjet_unkown_E_);
  tree->SetBranchAddress("ppfjet_electron_E",&pjet_electron_E_);
  tree->SetBranchAddress("ppfjet_muon_E",&pjet_muon_E_);
  tree->SetBranchAddress("ppfjet_photon_E",&pjet_photon_E_);
  tree->SetBranchAddress("ppfjet_unkown_px",&pjet_unkown_px_);
  tree->SetBranchAddress("ppfjet_electron_px",&pjet_electron_px_);
  tree->SetBranchAddress("ppfjet_muon_px",&pjet_muon_px_);
  tree->SetBranchAddress("ppfjet_photon_px",&pjet_photon_px_);
  tree->SetBranchAddress("ppfjet_unkown_py",&pjet_unkown_py_);
  tree->SetBranchAddress("ppfjet_electron_py",&pjet_electron_py_);
  tree->SetBranchAddress("ppfjet_muon_py",&pjet_muon_py_);
  tree->SetBranchAddress("ppfjet_photon_py",&pjet_photon_py_);
  tree->SetBranchAddress("ppfjet_unkown_pz",&pjet_unkown_pz_);
  tree->SetBranchAddress("ppfjet_electron_pz",&pjet_electron_pz_);
  tree->SetBranchAddress("ppfjet_muon_pz",&pjet_muon_pz_);
  tree->SetBranchAddress("ppfjet_photon_pz",&pjet_photon_pz_);
  tree->SetBranchAddress("ppfjet_unkown_EcalE",&pjet_unkown_EcalE_);
  tree->SetBranchAddress("ppfjet_electron_EcalE",&pjet_electron_EcalE_);
  tree->SetBranchAddress("ppfjet_muon_EcalE",&pjet_muon_EcalE_);
  tree->SetBranchAddress("ppfjet_photon_EcalE",&pjet_photon_EcalE_);
  tree->SetBranchAddress("ppfjet_unkown_n",&pjet_unkown_n_);
  tree->SetBranchAddress("ppfjet_electron_n",&pjet_electron_n_);
  tree->SetBranchAddress("ppfjet_muon_n",&pjet_muon_n_);
  tree->SetBranchAddress("ppfjet_photon_n",&pjet_photon_n_);
  tree->SetBranchAddress("ppfjet_had_n",&pjet_had_n_);
  tree->SetBranchAddress("ppfjet_had_E",&pjet_had_E_);
  tree->SetBranchAddress("ppfjet_had_px",&pjet_had_px_);
  tree->SetBranchAddress("ppfjet_had_py",&pjet_had_py_);
  tree->SetBranchAddress("ppfjet_had_pz",&pjet_had_pz_);
  tree->SetBranchAddress("ppfjet_had_EcalE",&pjet_had_EcalE_);
  tree->SetBranchAddress("ppfjet_had_rawHcalE",&pjet_had_rawHcalE_);
  tree->SetBranchAddress("ppfjet_had_emf",&pjet_had_emf_);
  tree->SetBranchAddress("ppfjet_had_id",&pjet_had_id_);
  tree->SetBranchAddress("ppfjet_had_candtrackind",&pjet_had_candtrackind_);
  if(isMC){
    tree->SetBranchAddress("ppfjet_had_E_mctruth",&pjet_had_E_mctruth_);
    tree->SetBranchAddress("ppfjet_had_mcpdgId",&pjet_had_mcpdgId_);
  }
  tree->SetBranchAddress("ppfjet_had_ntwrs",&pjet_had_ntwrs_);
  tree->SetBranchAddress("ppfjet_ntwrs",&pjet_ntwrs_);
  tree->SetBranchAddress("ppfjet_twr_ieta",&pjet_twr_ieta_);
  tree->SetBranchAddress("ppfjet_twr_iphi",&pjet_twr_iphi_);
  tree->SetBranchAddress("ppfjet_twr_hade",&pjet_twr_hade_);
  tree->SetBranchAddress("ppfjet_twr_frac",&pjet_twr_frac_);
  tree->SetBranchAddress("ppfjet_twr_candtrackind",&pjet_twr_candtrackind_);
  tree->SetBranchAddress("ppfjet_twr_hadind",&pjet_twr_hadind_);
  tree->SetBranchAddress("ppfjet_twr_elmttype",&pjet_twr_elmttype_);
  tree->SetBranchAddress("ppfjet_twr_dR",&pjet_twr_dR_);
  tree->SetBranchAddress("ppfjet_twr_clusterind",&pjet_twr_clusterind_);
  tree->SetBranchAddress("ppfjet_cluster_n",&pjet_cluster_n_);
  tree->SetBranchAddress("ppfjet_cluster_eta",&pjet_cluster_eta_);
  tree->SetBranchAddress("ppfjet_cluster_phi",&pjet_cluster_phi_);
  tree->SetBranchAddress("ppfjet_cluster_dR",&pjet_cluster_dR_);
  tree->SetBranchAddress("ppfjet_twr_subdet",&pjet_twr_subdet_);
  tree->SetBranchAddress("ppfjet_ncandtracks",&pjet_ncandtracks_);
  tree->SetBranchAddress("ppfjet_candtrack_px",&pjet_candtrack_px_);
  tree->SetBranchAddress("ppfjet_candtrack_py",&pjet_candtrack_py_);
  tree->SetBranchAddress("ppfjet_candtrack_pz",&pjet_candtrack_pz_);
  tree->SetBranchAddress("ppfjet_candtrack_EcalE",&pjet_candtrack_EcalE_);
  tree->SetBranchAddress("pf_dijet_deta",&dijet_deta_);
  tree->SetBranchAddress("pf_dijet_dphi",&dijet_dphi_);
  tree->SetBranchAddress("pf_dijet_balance",&dijet_balance_);
  tree->SetBranchAddress("pf_thirdjet_px",&thirdjet_px_);
  tree->SetBranchAddress("pf_thirdjet_py",&thirdjet_py_);
  tree->SetBranchAddress("pf_Run",&pf_Run_);
  tree->SetBranchAddress("pf_Lumi",&pf_Lumi_);
  tree->SetBranchAddress("pf_Event",&pf_Event_);
  tree->SetBranchAddress("pf_NPV",&pf_NPV_);
  if(isMC){
    tree->SetBranchAddress("pf_weight",&weight_);
  }
  else{
    weight_ = 1.0;
  }

  TH1D* h_PassSel_ = new TH1D("h_PassSelection", "Selection Pass Failures",256,-0.5,255.5);
  int fails = 0;

  int nEvents = tree->GetEntries();
  cout << "Running over " << nEvents << " events" << endl;
  //nEvents = 5;
  for(int iEvent=0; iEvent<nEvents; iEvent++){
    if(iEvent % 10000 == 0){
      cout << "Processing event " << iEvent << endl;
    }
    tree->GetEntry(iEvent);
    
    int passSel = 0;

    if(tjet_ntwrs_ == 0 || pjet_ntwrs_ == 0){
      fails++;
      passSel |= 0x80;
      //cout << "Fails: " << iEvent << " " << tjet_ntwrs_ << " " << pjet_ntwrs_ << endl;
      //continue;
    }
    float tjet_Et = tjet_E_/cosh(tjet_eta_);
    float pjet_Et = pjet_E_/cosh(pjet_eta_);
    float minSumJetEt_ = 0.0;//40.0;
    //float minJetEt_ = 50.0;//20.0;
    //float maxThirdJetEt_ = 15.0;//15.0;
    //float maxDeltaEta_ = 0.5;//0.5;
    //float maxJetEMFrac = 1.1;
    if(tjet_Et + pjet_Et < minSumJetEt_) passSel |= 0x1;
    if((tjet_Et > pjet_Et && tjet_Et < minJetEt_) || (tjet_Et <= pjet_Et && pjet_Et < minJetEt_)) passSel |= 0x2;
    if(sqrt(thirdjet_px_*thirdjet_px_ + thirdjet_py_*thirdjet_py_) > maxThirdJetEt_) passSel |= 0x4;
    if(dijet_deta_ > maxDeltaEta_) passSel |= 0x8;
    //if(tjet_EMfrac_ > maxJetEMFrac || pjet_EMfrac_ > maxJetEMFrac) passSel |= 0x100;
    if(tjet_jetID_ != 3 || pjet_jetID_ != 3) passSel |= 0x100;
    
    h_PassSel_->Fill(passSel);
    if(passSel) continue;

    DijetRespCorrDatum datum;
    
    // Fill datum
    //datum.SetWeight(weight_);
    datum.SetWeight(1.0);

    float sumt = 0;
    datum.SetTagEta(tjet_eta_);
    datum.SetTagPhi(tjet_phi_);
    for(int i=0; i<tjet_ntwrs_; i++){
      if(tjet_twr_hade_->at(i) > 0.0 && (tjet_twr_clusterind_->at(i) < 0 || tjet_cluster_dR_->at(tjet_twr_clusterind_->at(i)) < 0.5)){
	datum.AddTagHcalE(tjet_twr_hade_->at(i)*tjet_twr_frac_->at(i),tjet_twr_ieta_->at(i));
	sumt += tjet_twr_hade_->at(i)*tjet_twr_frac_->at(i);
      }
    }

    float tjet_had_EcalE_total = 0;
    float tjet_had_candNoRecHits_E = 0;
    for(int iHad=0; iHad<tjet_had_n_; iHad++){
      if(tjet_had_id_->at(iHad) < 2) tjet_had_EcalE_total += tjet_had_EcalE_->at(iHad);
      if(tjet_had_ntwrs_->at(iHad) == 0 && tjet_had_candtrackind_->at(iHad) > -1){
	tjet_had_candNoRecHits_E += sqrt(tjet_candtrack_px_->at(tjet_had_candtrackind_->at(iHad))*tjet_candtrack_px_->at(tjet_had_candtrackind_->at(iHad)) + tjet_candtrack_py_->at(tjet_had_candtrackind_->at(iHad))*tjet_candtrack_py_->at(tjet_had_candtrackind_->at(iHad)) + tjet_candtrack_pz_->at(tjet_had_candtrackind_->at(iHad))*tjet_candtrack_pz_->at(tjet_had_candtrackind_->at(iHad))) - tjet_had_EcalE_->at(iHad);
      }
    }
    datum.SetTagEcalE(tjet_unkown_E_ + tjet_electron_E_ + tjet_muon_E_ + tjet_photon_E_ + tjet_had_EcalE_total + tjet_had_candNoRecHits_E - getNeutralPUCorr(tjet_eta_,pf_NPV_,tjet_area_,isMC));

    float sump = 0;
    datum.SetProbeEta(pjet_eta_);
    datum.SetProbePhi(pjet_phi_);
    for(int i=0; i<pjet_ntwrs_; i++){
      if(pjet_twr_hade_->at(i) > 0.0 && (pjet_twr_clusterind_->at(i) < 0 || pjet_cluster_dR_->at(pjet_twr_clusterind_->at(i)) < 0.5)){
	datum.AddProbeHcalE(pjet_twr_hade_->at(i)*pjet_twr_frac_->at(i),pjet_twr_ieta_->at(i));
	sump += pjet_twr_hade_->at(i)*pjet_twr_frac_->at(i);
      }
    }

    float pjet_had_EcalE_total = 0;
    float pjet_had_candNoRecHits_E = 0;
    for(int iHad=0; iHad<pjet_had_n_; iHad++){
      if(pjet_had_id_->at(iHad) < 2) pjet_had_EcalE_total += pjet_had_EcalE_->at(iHad);
      if(pjet_had_ntwrs_->at(iHad) == 0 && pjet_had_candtrackind_->at(iHad) > -1){
	pjet_had_candNoRecHits_E += sqrt(pjet_candtrack_px_->at(pjet_had_candtrackind_->at(iHad))*pjet_candtrack_px_->at(pjet_had_candtrackind_->at(iHad)) + pjet_candtrack_py_->at(pjet_had_candtrackind_->at(iHad))*pjet_candtrack_py_->at(pjet_had_candtrackind_->at(iHad)) + pjet_candtrack_pz_->at(pjet_had_candtrackind_->at(iHad))*pjet_candtrack_pz_->at(pjet_had_candtrackind_->at(iHad))) - pjet_had_EcalE_->at(iHad);
      }
    }
    datum.SetProbeEcalE(pjet_unkown_E_ + pjet_electron_E_ + pjet_muon_E_ + pjet_photon_E_ + pjet_had_EcalE_total + pjet_had_candNoRecHits_E - getNeutralPUCorr(pjet_eta_,pf_NPV_,pjet_area_,isMC));

    datum.SetThirdJetPx(thirdjet_px_);
    datum.SetThirdJetPy(thirdjet_py_);

    if(sumt == 0 || sump == 0){
      fails++;
      continue;
    }
    

    data.push_back(datum);
  }

  cout << data.GetSize() << " data" << endl;
  
  cout << "Passes: " << nEvents - fails << " Fails: " << fails << endl;
  cout << "Do CandTrack? " << data.GetDoCandTrackEnergyDiff() << endl;
  data.SetDoCandTrackEnergyDiff(false);
  cout << "Do CandTrack? " << data.GetDoCandTrackEnergyDiff() << endl;

  //return 0;
  
  TH1D* hist = data.doFit("h_corr","Response Corrections");
  hist->GetXaxis()->SetTitle("i_{#eta}");
  hist->GetYaxis()->SetTitle("response corrections");

  TFile* fout = new TFile(output,"RECREATE");
  fout->cd();
  hist->Write();
  h_PassSel_->Write();
  fout->Close();

  cout << "Passes: " << nEvents - fails << " Fails: " << fails << endl;
  cout << "Events that passed cuts: " << h_PassSel_->GetBinContent(1) << endl;
  
  return 0;
}

double getNeutralPUCorr(double eta, int intNPV, double area, bool isMC_)
{
  double NPV = static_cast<double>(intNPV);
  double etaArray[101] = {-5, -4.9, -4.8, -4.7, -4.6, -4.5, -4.4, -4.3, -4.2, -4.1, -4, -3.9, -3.8, -3.7, -3.6, -3.5, -3.4, -3.3, -3.2, -3.1, -3, -2.9, -2.8, -2.7, -2.6, -2.5, -2.4, -2.3, -2.2, -2.1, -2, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5};

  int ind = -1;
  for(int i=0; i<100; ++i){
    if(eta > etaArray[i] && eta < etaArray[i+1]){
      ind = i;
      break;
    }
  }
  if(ind < 0) return 0;

  double pt_density;
  if(isMC_){
    double p0[100] = {0.08187, 0.096718, 0.11565, 0.12115, 0.12511, 0.12554, 0.13858, 0.14282, 0.14302, 0.15054, 0.14136, 0.14992, 0.13812, 0.13771, 0.13165, 0.12609, 0.12446, 0.11311, 0.13771, 0.16401, 0.20454, 0.27899, 0.34242, 0.43096, 0.50742, 0.59683, 0.66877, 0.68664, 0.69541, 0.66873, 0.64175, 0.61097, 0.58524, 0.5712, 0.55752, 0.54869, 0.31073, 0.22667, 0.55614, 0.55962, 0.54348, 0.53206, 0.51594, 0.49928, 0.49139, 0.48766, 0.49157, 0.49587, 0.50109, 0.5058, 0.51279, 0.51515, 0.51849, 0.52607, 0.52362, 0.52169, 0.53579, 0.54821, 0.56262, 0.58355, 0.58809, 0.57525, 0.52539, 0.53505, 0.52307, 0.52616, 0.52678, 0.53536, 0.55141, 0.58107, 0.60556, 0.62601, 0.60897, 0.59018, 0.49593, 0.40462, 0.32052, 0.24436, 0.18867, 0.12591, 0.095421, 0.090578, 0.078767, 0.11797, 0.14057, 0.14614, 0.15232, 0.14742, 0.15647, 0.14947, 0.15805, 0.14467, 0.14526, 0.14081, 0.1262, 0.12429, 0.11951, 0.11146, 0.095677, 0.083126};
    double p1[100] = {0.26831, 0.30901, 0.37017, 0.38747, 0.41547, 0.45237, 0.49963, 0.54074, 0.54949, 0.5937, 0.56904, 0.60766, 0.58042, 0.59823, 0.58535, 0.54594, 0.58403, 0.601, 0.65401, 0.65049, 0.65264, 0.6387, 0.60646, 0.59669, 0.55561, 0.5053, 0.42889, 0.37264, 0.36456, 0.36088, 0.36728, 0.37439, 0.38779, 0.40133, 0.40989, 0.41722, 0.47539, 0.49848, 0.42642, 0.42431, 0.42113, 0.41285, 0.41003, 0.41116, 0.41231, 0.41634, 0.41795, 0.41806, 0.41786, 0.41765, 0.41779, 0.41961, 0.42144, 0.42192, 0.4209, 0.41885, 0.4163, 0.4153, 0.41864, 0.4257, 0.43018, 0.43218, 0.43798, 0.42723, 0.42185, 0.41349, 0.40553, 0.39132, 0.3779, 0.37055, 0.36522, 0.37057, 0.38058, 0.43259, 0.51052, 0.55918, 0.60178, 0.60995, 0.64087, 0.65554, 0.65308, 0.65654, 0.60466, 0.58678, 0.54392, 0.58277, 0.59651, 0.57916, 0.60744, 0.56882, 0.59323, 0.5499, 0.54003, 0.49938, 0.4511, 0.41499, 0.38676, 0.36955, 0.30803, 0.26659};
    double p2[100] = {0.00080918, 0.00083447, 0.0011378, 0.0011221, 0.0013613, 0.0016362, 0.0015854, 0.0019131, 0.0017474, 0.0020078, 0.001856, 0.0020331, 0.0020823, 0.001898, 0.0020096, 0.0016464, 0.0032413, 0.0045615, 0.0054495, 0.0057584, 0.0058982, 0.0058956, 0.0055109, 0.0051433, 0.0042098, 0.0032096, 0.00044089, -0.0003884, -0.0007059, -0.00092769, -0.001116, -0.0010437, -0.00080318, -0.00044142, 6.7232e-05, 0.00055265, -0.0014486, -0.0020432, 0.0015121, 0.0016343, 0.0015638, 0.0015707, 0.0014403, 0.0012886, 0.0011684, 0.00099089, 0.00091497, 0.00087915, 0.00084703, 0.00084542, 0.00087419, 0.00088013, 0.00090493, 0.00095853, 0.0010389, 0.0011191, 0.0012643, 0.0013833, 0.001474, 0.0015401, 0.0015582, 0.0014265, 0.00087453, 0.00086639, 0.00042986, -5.0257e-06, -0.00053124, -0.00086417, -0.0011228, -0.0011749, -0.0010068, -0.00083012, -0.00062906, 0.00021515, 0.0028714, 0.0038835, 0.0047212, 0.0051427, 0.0055762, 0.0055872, 0.0054989, 0.0053033, 0.0044519, 0.0032223, 0.0017641, 0.0021165, 0.0019909, 0.0021061, 0.0020322, 0.0018357, 0.0019829, 0.001683, 0.0018553, 0.0015304, 0.0015822, 0.0013119, 0.0010745, 0.0010808, 0.00080678, 0.00079756};
    pt_density = p0[ind] + p1[ind]*(NPV - 1) + p2[ind]*(NPV - 1)*(NPV - 1);
  }
  else{
    double p0[100] = {0.12523, 0.14896, 0.17696, 0.19376, 0.20038, 0.21353, 0.25069, 0.27089, 0.29124, 0.31947, 0.31781, 0.35453, 0.35424, 0.38159, 0.39453, 0.4003, 0.34798, 0.26303, 0.24824, 0.22857, 0.22609, 0.26793, 0.30096, 0.37637, 0.44461, 0.55692, 0.70328, 0.72458, 0.75065, 0.73569, 0.72485, 0.69933, 0.69804, 0.70775, 0.70965, 0.71439, 0.72189, 0.73691, 0.74847, 0.74968, 0.73467, 0.70115, 0.6732, 0.65971, 0.65724, 0.67751, 0.69569, 0.70905, 0.71815, 0.72119, 0.72128, 0.71645, 0.70588, 0.68958, 0.66978, 0.65959, 0.66889, 0.68713, 0.71063, 0.74283, 0.75153, 0.74733, 0.73335, 0.71346, 0.70168, 0.69445, 0.68841, 0.67761, 0.67654, 0.6957, 0.70276, 0.71057, 0.68176, 0.64651, 0.49156, 0.38366, 0.31375, 0.24127, 0.21395, 0.17783, 0.19026, 0.21486, 0.24689, 0.3434, 0.40184, 0.39876, 0.3873, 0.36462, 0.36337, 0.32777, 0.328, 0.29868, 0.28087, 0.25713, 0.22466, 0.20784, 0.19798, 0.18054, 0.15022, 0.12811};
    double p1[100] = {0.26829, 0.30825, 0.37034, 0.38736, 0.41645, 0.45985, 0.51433, 0.56215, 0.5805, 0.63926, 0.62007, 0.67895, 0.66015, 0.68817, 0.67975, 0.64161, 0.70887, 0.74454, 0.80197, 0.78873, 0.77892, 0.74943, 0.70034, 0.6735, 0.60774, 0.53312, 0.42132, 0.36279, 0.3547, 0.35014, 0.35655, 0.3646, 0.37809, 0.38922, 0.39599, 0.40116, 0.40468, 0.40645, 0.40569, 0.4036, 0.39874, 0.39326, 0.39352, 0.39761, 0.40232, 0.40729, 0.41091, 0.41247, 0.413, 0.41283, 0.41289, 0.4134, 0.41322, 0.41185, 0.40769, 0.40193, 0.39707, 0.39254, 0.39274, 0.3989, 0.40474, 0.40758, 0.40788, 0.40667, 0.40433, 0.40013, 0.39371, 0.38154, 0.36723, 0.3583, 0.35148, 0.35556, 0.36172, 0.41073, 0.50629, 0.57068, 0.62972, 0.65188, 0.69954, 0.72967, 0.74333, 0.76148, 0.71418, 0.69062, 0.63065, 0.67117, 0.68278, 0.66028, 0.68147, 0.62494, 0.64452, 0.58685, 0.57076, 0.52387, 0.47132, 0.42637, 0.39554, 0.37989, 0.31825, 0.27969};
    double p2[100] = {-0.0014595, -0.0014618, -0.0011988, -0.00095404, -5.3893e-05, 0.00018901, 0.00012553, 0.0004172, 0.00020229, 0.00051942, 0.00052088, 0.00076727, 0.0010407, 0.0010184, 0.0013442, 0.0011271, 0.0032841, 0.0045259, 0.0051803, 0.0054477, 0.0055691, 0.0056668, 0.0053084, 0.0050978, 0.0042061, 0.003321, 0.00045155, 0.00021376, 0.0001178, -2.6836e-05, -0.00017689, -0.00014723, 0.00016887, 0.00067322, 0.0012952, 0.0019229, 0.0024702, 0.0028854, 0.0031576, 0.003284, 0.0032643, 0.0031061, 0.0028377, 0.0025386, 0.0022583, 0.0020448, 0.001888, 0.0017968, 0.0017286, 0.0016989, 0.0017014, 0.0017302, 0.0017958, 0.0018891, 0.0020609, 0.0022876, 0.0025391, 0.0028109, 0.0030294, 0.0031867, 0.0032068, 0.0030755, 0.0028181, 0.0023893, 0.0018359, 0.0012192, 0.00061654, 0.00016088, -0.00015204, -0.00019503, -3.7236e-05, 0.00016663, 0.00033833, 0.00082988, 0.0034005, 0.0042941, 0.0050884, 0.0052612, 0.0055901, 0.0054357, 0.0052671, 0.0049174, 0.0042236, 0.0031138, 0.0011733, 0.0014057, 0.0010843, 0.0010992, 0.0007966, 0.00052196, 0.00053029, 0.00021273, 0.00041664, 0.00010455, 0.00015173, -9.7827e-05, -0.0010859, -0.0013748, -0.0016641, -0.0016887};
    pt_density = p0[ind] + p1[ind]*(NPV - 1) + p2[ind]*(NPV - 1)*(NPV - 1);
  }

  double ECorr = pt_density*area*cosh(eta);

  return ECorr;
}
