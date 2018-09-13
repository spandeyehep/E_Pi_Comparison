// program to plot 3D histograms , graphs etc.

// ROOT scrxipt to build a 2D hostogram.

#include<TFile.h>
#include<TH3F.h>
#include<TH1F.h>
#include<TCanvas.h>

void Beautify(TH3F*,TCanvas*);
void ThreeDPlot()
{
  int nbins=10;
  // TFile* tf = new TFile("A2Sample2.root");
  TFile* tf = new TFile("ShowerDev.root");
  TCanvas* tc=new TCanvas("arg1","arg2",800,600);
  // for(int i=1;i<4;i++){
    char* HName1=new char[50];
    char* HName2=new char[50];
    // sprintf(HName,"LocationEvt%d",10*i);
    sprintf(HName1,"EShower");
    sprintf(HName2,"PShower");
    TH3F* HPlot1=(TH3F*)tf->Get(HName1);
    TH3F* HPlot2=(TH3F*)tf->Get(HName2);
    // HPlot->GetXaxis()->SetTitle("X");
    // HPlot->GetYaxis()->SetTitle("y");
    // HPlot->GetZaxis()->SetTitle("Z");
    // HPlot->SetStats(0);
    // HPlot->SetMarkerStyle(4);
    // HPlot->Draw("hist");
    // HPlot->SetMarkerColor(9);
    // HPlot->SetMarkerStyle(21);
    // char* iname=new char[70];
    // sprintf(iname,"%s.png",HName);
    // tc->SaveAs(iname);
    Beautify(HPlot1,tc);
    char* iname1=new char[70];
    sprintf(iname1,"%s.png",HName1);
    tc->SaveAs(iname1);

    Beautify(HPlot2,tc);
    char* iname2=new char[70];
    sprintf(iname2,"%s.png",HName2);
    tc->SaveAs(iname2);
// }
  tc->Close();
  tf->Close();
}

void Beautify(TH3F* h,TCanvas* tc)
{
  h->GetXaxis()->SetTitle("Z");
  h->GetYaxis()->SetTitle("y");
  h->GetZaxis()->SetTitle("X");
  // Note : X is exchanged with Z
  h->SetStats(0);
  h->SetMarkerSize(1);
  h->Draw("hist");
  h->SetMarkerColor(9);
  h->SetMarkerStyle(1);
}
