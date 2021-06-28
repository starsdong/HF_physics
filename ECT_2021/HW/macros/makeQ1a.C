#include "stdio.h"
#include <iomanip.h>

void makeQ1a()
{
  gROOT->Reset();

  const Int_t N = 10;
  Char_t *FileName[N] = {"../data/PHSD/charm/homework1a-phsd.dat",
			 "../data/CUJET/CUJET/CUJET_Trasport_Coefficient.dat",
			 "../data/Duke/Ds2PiT_0.dat",
			 "../data/TAMU/Z_results-data/1a_Ds2piT.txt",
			 "../data/Catania/Dx_Charm.dat",
			 "../data/LBT/LBT/data-1a-LBT-2piTD-p-10.dat",
			 "../data/Nantes/task1/2piDsT.txt",
			 "../data/Nantes/task1/2piDsT_el.txt",
			 "../data/DAB-MOD/Ds2PiT.txt",
			 "../data/LQCD/ds_scale.root"};
  //			 "../data/LQCD/fit_ds_scale.root"};
  const Char_t *Name[N] = {"PHSD","CUJET","Duke","TAMU","Catania","LBT","Nantes","Nantes el.","DAB-MOD","LQCD"};
  const Int_t Color[N] = {kBlack, kRed, kGreen+2, kBlue, kOrange+1, kGray+2, kMagenta+1, kMagenta+1, kAzure+1, kBlack};
  const Int_t Style[N] = {1, 2, 3, 9, 5, 6, 7, 8, 4, 10};
  TGraph *gr[N];
  for(int i=0;i<N-1;i++) {
    gr[i] = new TGraph(FileName[i],"%lg %lg");
    gr[i]->SetLineWidth(2);
    gr[i]->SetLineColor(Color[i]);
    gr[i]->SetLineStyle(Style[i]);
  }

  TFile *fin = new TFile(FileName[N-1]);
  TGraphAsymmErrors *gr_LQCD = (TGraphAsymmErrors *)fin->Get("2piTDs_LQCD");
  gr_LQCD->SetMarkerStyle(20);
  gr_LQCD->SetMarkerSize(1.5);
  gr_LQCD->SetLineWidth(2);
  gr_LQCD->SetFillColor(5);
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,1000,800);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetErrorX(0.05);
  c1->SetFillColor(10);
  c1->SetFillStyle(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(0);
  c1->SetFrameFillColor(10);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  //  c1->SetLogy();
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetGridx(0);
  c1->SetGridy(0);
  c1->SetLeftMargin(0.13);
  c1->SetBottomMargin(0.14);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);

  double x1 = 0.0;
  double x2 = 0.65;
  double y1 = 0.;
  double y2 = 25.;

  
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(505);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("T (GeV)");
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.045);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(52);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("2#piTD_{s}(p=0)");
  h0->GetYaxis()->SetTitleOffset(0.8);
  h0->GetYaxis()->SetTitleSize(0.07);
  h0->GetYaxis()->SetLabelOffset(0.015);
  h0->GetYaxis()->SetLabelSize(0.045);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(52);
  h0->Draw("c");

  TLine *l1 = new TLine(x1,y1,x2,y1);
  l1->SetLineWidth(3);
  l1->Draw("same");
  TLine *l2 = new TLine(x1,y2,x2,y2);
  l2->SetLineWidth(3);
  l2->Draw("same");
  TLine *l3 = new TLine(x1,y1,x1,y2);
  l3->SetLineWidth(3);
  l3->Draw("same");
  TLine *l4 = new TLine(x2,y1,x2,y2);
  l4->SetLineWidth(3);
  l4->Draw("same");

  //  gr_LQCD->Draw("e3");
  gr_LQCD->Draw("p");
  for(int i=0;i<N-1;i++) {
    gr[i]->Draw("c");
  }

  TLegend *leg = new TLegend(0.16, 0.96-N*0.055, 0.40, 0.96);
  leg->SetFillColor(10);
  //   leg->SetFillStyle(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  for(int i=0;i<N-1;i++) leg->AddEntry(gr[i],Name[i],"l");
  leg->AddEntry(gr_LQCD,Name[N-1],"p");
  leg->Draw();
  
  
  c1->Update();
  c1->SaveAs("../fig/Q1a_2piTDs.pdf");
  c1->SaveAs("../fig/Q1a_2piTDs.png"); 
  
}
