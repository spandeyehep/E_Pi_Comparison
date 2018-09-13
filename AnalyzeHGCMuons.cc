#define ANALYZEHGCMuons_cxx

#include <iostream>
#include <vector>
#include <cstring>
#include "AnalyzeHGCMuons.h"

using namespace std;



// chip 3022,44,3028




int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  AnalyzeHGCMuons hgcmuons(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  hgcmuons.EventLoop(data);
  return 0;
}

void AnalyzeHGCMuons::EventLoop(const char *data) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes2 = 0, nb2 = 0;
  int decade = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // if(jentry != 10044 ) continue;
    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" << endl;
    decade = k;
    
    // ===============read this entry == == == == == == == == == == == 
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    nb2 = fChain2->GetEntry(jentry);   nbytes2 += nb2;

    h_nrechits->Fill(NRechits);
    // std::cout << jentry << " Run " << run << "  Event " << event << " beamEnergy " << beamEnergy 
    // 	      << " NRechits " << NRechits << std::endl;

    // if(jentry<1000){
    //   cout<<"Rechit_channel= "<<rechit_channel->size();
    //   cout<<"\tRechit_chip= "<<rechit_chip->size();
    //   cout<<"\t\tRechit_layer= "<<rechit_layer->size()<<endl;
    // }
    Assignment1(jentry);
  } // loop over entries
}

void AnalyzeHGCMuons::Assignment1(int jentry)
{
  // int n1=rechit_layer->size();
  // for(int i=0;i<rechit_channel->size();i++){
  //   if(rechit_chip->at(i)==2){
  //     h_Chip3_rechits->Fill(rechit_layer->at(i),rechit_channel->at(i));
  //   }
  // }
  // for(int i=0;i<n1;i++){
  //   int* q=&i;
  //   int temp=rechit_layer->at(i);
  //   if(temp==28){
  //     h_layered_nrechits[27]->Fill(n1-i);
  //     *q=n1;
  //     break;
  //   }
  //   for(int j=0;j<n1-i;j++){
  //     if(temp==15){		// Loop for debugging Layer 15
  // 	h_Debug15->Fill(jentry);
  // 	h_Debug15geom->Fill(rechit_chip->at(i+j),rechit_channel->at(i+j));
  //     }
  //     if(rechit_layer->at(i+j)!=temp){
  // 	h_layered_nrechits[temp-1]->Fill(j);
  // 	*q=*q+j-1;
  // 	break;
  //     }
  //   }
  // }
  if(NRechits<100){
    for(int i=0;i<rechit_x->size();i++){
      h_Electron->Fill(rechit_z->at(i),rechit_y->at(i),rechit_x->at(i));
	}
  }
  if(NRechits>500){
    for(int i=0;i<rechit_x->size();i++){
      h_Pion->Fill(rechit_z->at(i),rechit_y->at(i),rechit_x->at(i));
	}
  }
  if(jentry==10){
    for(int i=0;i<rechit_layer->size();i++){
      h_PerEventShower[0]->Fill(rechit_layer->at(i));
      h_ShowerDev[0]->Fill(rechit_z->at(i),rechit_y->at(i),rechit_x->at(i));
      h_ShowerX[0]->Fill(rechit_x->at(i));
      h_ShowerY[0]->Fill(rechit_y->at(i));
    }
  }
  if(jentry==20){
    for(int i=0;i<rechit_layer->size();i++){
      h_PerEventShower[1]->Fill(rechit_layer->at(i));
      h_ShowerDev[1]->Fill(rechit_z->at(i),rechit_y->at(i),rechit_x->at(i));
      h_ShowerX[1]->Fill(rechit_x->at(i));
      h_ShowerY[1]->Fill(rechit_y->at(i));
      // cout<<"";
    }
  }
  if(jentry==30){
    for(int i=0;i<rechit_layer->size();i++){
      h_PerEventShower[2]->Fill(rechit_layer->at(i));
      h_ShowerDev[2]->Fill(rechit_z->at(i),rechit_y->at(i),rechit_x->at(i));
      h_ShowerX[2]->Fill(rechit_x->at(i));
      h_ShowerY[2]->Fill(rechit_y->at(i));
    }
  }
  // float in=0;
  // float fin=0;
  // int n1=15;			// number of layers under consideration
  // for(int i=0;i<rechit_layer->size();i++){
  //   if(rechit_layer->at(i)<=n1){in++;}
  //   if(rechit_layer->at(i)>28-n1){fin++;}
  // }
  // if(fin==0){h_ratio->Fill(-1);}
  // else{h_ratio->Fill(in/fin);}
  float in_NR=0;
  float in_En=0;

  float fin_NR=rechit_layer->size();
  float fin_En=0;
  for(int i=0;i<rechit_energy->size();i++){fin_En+=rechit_energy->at(i);}

  for(int n=1;n<=28;n++){
    float in_ratio=0;
    float fin_ratio=0;
    
    int n1=n;			// number of layers under consideration
    for(int i=0;i<rechit_layer->size();i++){
      if(rechit_layer->at(i)<=n1){in_ratio++;}
      if(rechit_layer->at(i)>28-n1){fin_ratio++;}
      if(rechit_layer->at(i)==n){in_NR++;in_En+=rechit_energy->at(i);}
    }
    if(fin_ratio==0){h_RatioCheck->Fill(n1,-1);}
    else{h_RatioCheck->Fill(n1,in_ratio/fin_ratio);}
    h_CumuNRechits->Fill(n,in_NR/fin_NR);
    h_CumuEnergy->Fill(n,in_En/fin_En);
  }
}
