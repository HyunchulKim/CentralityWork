//####################
//  MakeReducedTrees
// - From HiForest files, only extract trees what we need to run
// Hyunchul.kim@cern.ch, worldtoi@gmail.com
//####################

#include <iostream>
#include <fstream>
#include <TChain.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>

void MakeReducedTrees() {

   // Call the trees what we want to save (others will be skipped)
   TChain *t_evt = new TChain("hiEvtAnalyzer/HiTree");
   TChain *t_skim = new TChain("skimanalysis/HltTree");
   TChain *t_hlt = new TChain("hltanalysis/HltTree");
   TChain *t_zdcrechit = new TChain("rechitanalyzerpp/zdcrechit");

   // 
	TString FileName="list_run327554_noZBlimit";
	ifstream openFile(FileName.Data());
	if ( openFile.is_open() )
	{
		std::string line;
		while(getline(openFile, line))
		{
			std::cout << line << std::endl;
			//chain->Add(line.data());
			t_evt->Add(line.data());
			t_skim->Add(line.data());
			t_hlt->Add(line.data());
			t_zdcrechit->Add(line.data());
			std::cout << "Entries : " << t_evt->GetEntries() << std::endl;			 	
		}
		openFile.close();
	}
	
	TFile* fout = new TFile("fout_20200721_addZDC_run327554.root","RECREATE");
	fout->cd();
	TDirectory *dir;

   dir = fout->mkdir("hiEvtAnalyzer");
   dir->cd();

   t_evt->CloneTree(-1,"fast");
   std::cout << "### hiEvtAnalyzer is cloned completely ###" << std::endl;

   dir = fout->mkdir("skimanalysis");
   dir->cd();
   t_skim->CloneTree(-1,"fast");
   std::cout << "### skimanalysis is cloned completely ###" << std::endl;

   dir = fout->mkdir("hltanalysis");
   dir->cd();
   t_hlt->SetBranchStatus("*",0);
   t_hlt->SetBranchStatus("Event",1);
   t_hlt->SetBranchStatus("LumiBlock",1);
   t_hlt->SetBranchStatus("Run",1);
   t_hlt->SetBranchStatus("Bx",1);
   t_hlt->SetBranchStatus("Orbit",1);
   t_hlt->SetBranchStatus("AvgInstDelLumi",1);
/*
   t_hlt->SetBranchStatus("HLT_HIL1_ZDC_AND_OR_MinimumBiasHF1_AND_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_HIL1_ZDC_AND_OR_MinimumBiasHF1_AND_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIL1_ZDC_AND_OR_MinimumBiasHF2_AND_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_HIL1_ZDC_AND_OR_MinimumBiasHF2_AND_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasHFOR_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasHFOR_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part0_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part0_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part10_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part10_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part11_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part11_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part12_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part12_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part13_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part13_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part14_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part14_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part15_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part15_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part16_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part16_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part17_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part17_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part18_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part18_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part19_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part19_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part1_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part1_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part20_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part20_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part21_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part21_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part22_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part22_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part23_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part23_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part2_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part2_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part3_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part3_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part4_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part4_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part5_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part5_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part6_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part6_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part7_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part7_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part8_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part8_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part9_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_SinglePixelTrack_part9_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part0_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part0_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part10_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part10_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part11_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part11_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part12_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part12_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part13_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part13_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part14_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part14_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part15_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part15_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part16_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part16_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part17_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part17_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part18_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part18_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part19_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part19_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part1_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part1_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part20_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part20_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part21_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part21_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part22_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part22_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part23_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part23_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part2_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part2_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part3_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part3_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part4_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part4_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part5_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part5_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part6_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part6_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part7_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part7_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part8_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part8_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part9_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF_part9_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part0_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part0_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part10_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part10_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part11_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part11_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part12_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part12_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part13_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part13_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part14_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part14_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part15_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part15_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part16_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part16_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part17_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part17_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part18_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part18_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part19_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part19_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part1_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part1_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part2_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part2_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part3_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part3_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part4_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part4_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part5_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part5_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part6_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part6_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part7_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part7_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part8_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part8_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part9_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part9_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part0_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part0_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part10_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part10_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part11_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part11_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part12_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part12_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part13_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part13_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part14_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part14_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part15_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part15_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part16_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part16_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part17_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part17_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part18_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part18_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part19_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part19_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part1_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part1_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part2_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part2_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part3_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part3_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part4_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part4_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part5_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part5_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part6_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part6_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part7_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part7_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part8_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part8_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part9_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part9_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part0_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part0_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part10_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part10_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part11_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part11_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part12_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part12_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part13_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part13_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part14_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part14_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part15_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part15_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part16_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part16_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part17_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part17_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part18_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part18_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part19_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part19_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part1_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part1_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part2_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part2_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part3_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part3_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part4_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part4_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part5_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part5_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part6_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part6_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part7_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part7_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part8_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part8_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part9_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part9_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part0_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part0_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part10_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part10_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part11_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part11_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part12_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part12_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part13_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part13_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part14_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part14_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part15_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part15_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part16_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part16_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part17_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part17_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part18_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part18_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part19_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part19_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part1_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part1_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part20_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part20_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part21_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part21_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part22_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part22_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part23_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part23_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part24_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part24_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part25_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part25_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part2_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part2_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part3_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part3_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part4_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part4_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part5_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part5_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part6_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part6_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part7_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part7_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part8_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part8_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part9_v1",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part9_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_HIZeroBias_v1",1);
   t_hlt->SetBranchStatus("HLT_HIZeroBias_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF1AND_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF1AND_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF1OR_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF1OR_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF2AND_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF2AND_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF2OR_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCAND_MBHF2OR_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_ZDCP_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_ZDCP_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_ZDCP_MBHF1AND_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_ZDCP_MBHF1AND_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCM_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCOR_MBHF1OR_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCOR_MBHF1OR_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCOR_MBHF2OR_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCOR_MBHF2OR_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCP_BptxAND_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCP_BptxAND_v1_Prescl",1);
   t_hlt->SetBranchStatus("HLT_ZDCP_v1",1);
   t_hlt->SetBranchStatus("HLT_ZDCP_v1_Prescl",1);
*/
   t_hlt->SetBranchStatus("HLT_HIZeroBias*",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_part*",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_part*",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part*",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part*",1);
   t_hlt->SetBranchStatus("HLT_HIMinimumBiasRF*",1);
 
   t_hlt->SetBranchStatus("HLT_*ZDC*",1);

   t_hlt->CloneTree();

   std::cout << "### hltanalysis is cloned completely ###" << std::endl;

   dir = fout->mkdir("rechitanalyzerpp");
   dir->cd();

   t_zdcrechit->CloneTree(-1,"fast");
   std::cout << "### zdcrechit tree is cloned completely ###" << std::endl;


   fout->Write();
   fout->Close();
   std::cout << "####### CLOSE #######" << std::endl;
   
}
