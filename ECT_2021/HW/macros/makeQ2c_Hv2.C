#include "stdio.h"
#include <iomanip.h>

void makeQ2c_Hv2()
{
  gROOT->Reset();

  const Int_t N = 10;
  const Int_t Ng = 2;
  Char_t *FileName[N] = {"../data/PHSD/homework2c_Hv2-phsd.txt",
			 "",
			 "",
			 "../data/TAMU/Z_results-data/2c_Hv2.txt",
			 "",
			 "",
			 "",
			 "",
			 "",
			 ""};
  //  Char_t *Name[N] = {"PHSD","CUJET","Duke","TAMU","Catania","DAB-MOD"};
  const Char_t *Name[N] = {"PHSD","CUJET","Duke","TAMU","Catania","LBT","Nantes","Nantes el.","DAB-MOD","LQCD"};
  const Int_t Color[N] = {kBlack, kRed, kGreen+2, kBlue, kOrange+1, kGray+2, kMagenta+1, kMagenta+1, kAzure+1, kBlack};
  const Int_t Style[N] = {1, 2, 3, 9, 5, 6, 7, 8, 4, 10};

  TGraph *gr[N];
  for(int i=0;i<N;i++) {
    if(i!=0 && i!=3) continue;
    gr[i] = new TGraph(FileName[i],"%lg %lg");
    gr[i]->SetLineWidth(2);
    gr[i]->SetLineColor(Color[i]);
    gr[i]->SetLineStyle(Style[i]);
  }

  
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
  double x2 = 24.9;
  double y1 = 0.;
  double y2 = 2.4;

  
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(505);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.045);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(52);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("H_{v2} = v_{2}^{FO}/v_{2}^{H}");
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

  for(int i=0;i<N;i++) {
    if(i!=0 && i!=3) continue;
    gr[i]->Draw("c");
  }

  TLegend *leg = new TLegend(0.74, 0.15, 0.95, 0.15+Ng*0.06);
  leg->SetFillColor(10);
  //   leg->SetFillStyle(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  for(int i=0;i<N;i++) {
    if(i!=0 && i!=3) continue;
    leg->AddEntry(gr[i],Name[i],"l");
  }
  leg->Draw();
  
  TLegend *leg = new TLegend(0.58, 0.85, 0.86, 0.95);
  leg->SetFillColor(10);
  //   leg->SetFillStyle(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->AddEntry("","Pb+Pb@5TeV, 30-50%","");
  leg->Draw();
  
  
  c1->Update();
  c1->SaveAs("../fig/Q2c_Hv2.pdf");
  c1->SaveAs("../fig/Q2c_Hv2.png"); 
  
}
