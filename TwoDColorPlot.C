// ROOT scrxipt to build a 2D hostogram.

#include<TFile.h>
#include<TH2F.h>
#include<TH1F.h>
#include<TCanvas.h>

void TwoDColorPlot()
{
  int nbins=60;
  // TFile* tf = new TFile("Output1.root");
  TFile* tf = new TFile("Output2.root");
  TH2F* HPlot=new TH2F("layeredRechits","rechits distribution per layer",30,0,30,nbins,0,nbins);
  TCanvas* tc=new TCanvas("arg1","arg2",1000,600);
  for(int layer=0;layer<28;layer++){
    char* HName=new char[50];
    sprintf(HName,"RC_layer_%d",layer+1);
    TH1F* temp=(TH1F*)tf->Get(HName);
    // for(int j=0;j<nbins;j++){
    for(int k=1;k<nbins;k++){
      // HPlot->Fill(layer,j+1,temp->GetBinContent(j));
      HPlot->Fill(layer+1,k-1,temp->GetBinContent(k));
      if(layer==14){cout<<"layer = "<<layer<<"\tk="<<k<<"\tBinContent(k) = "<<temp->GetBinContent(k)<<endl;}
    }
    temp->~TH1F();
  }
  HPlot->GetXaxis()->SetTitle("Layer index");
  HPlot->GetYaxis()->SetTitle("No. of rechits");
  HPlot->SetStats(0);
  HPlot->Draw("COLZ");
  // tc->SaveAs("LayeredRechits.root");
  // tc->SaveAs("LayeredRechits.png");
  tc->SaveAs("LayeredRechits_v11.root");
  tc->SaveAs("LayeredRechits_v11.png");
  tc->Close();
  tf->Close();
}
