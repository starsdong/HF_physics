#include <stdio.h>
#include "iomanip.h"

void make_DHQ_etaS_102020()
{
  gROOT->Reset();

  ifstream inData;
  const Double_t twoPi = 3.1415927*2.0;
  const Double_t fourPi = 3.1415927*4.0;
  const Double_t Tc = 154.;

  //eta/S
  inData.open("/Users/starsdong/work/datapoints/D_HQ/20201023/etaS_bayesian_naturephysics.txt");
  const Int_t n_etaS = 10;
  double x_etaS[n_etaS], y_etaS[n_etaS], ye1_etaS[n_etaS], ye2_etaS[n_etaS];
  for(int i=0;i<n_etaS;i++) {
    inData >> x_etaS[i] >> y_etaS[i] >> ye1_etaS[i] >> ye2_etaS[i];
    x_etaS[i] /= Tc;
    y_etaS[i] *= fourPi;
    ye1_etaS[i] *= fourPi;
    ye2_etaS[i] *= fourPi;
  }
  inData.close();
  TGraphAsymmErrors *gr_etaS = new TGraphAsymmErrors(n_etaS, x_etaS, y_etaS, 0, 0, ye1_etaS, ye2_etaS);
  TGraph *gr_etaS_0 = new TGraph(n_etaS, x_etaS, y_etaS);

  
  TGraph *gr_Duke_0 = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Duke_0.txt","%lg %lg");
  TGraph *gr_Duke_low = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Duke_low.txt","%lg %lg");
  TGraph *gr_Duke_high = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Duke_high.txt","%lg %lg");
  double x_Duke[100], y_Duke[100], ye_low_Duke[100], ye_high_Duke[100];
  for(int i=0;i<gr_Duke_0->GetN();i++) {
    x_Duke[i] = gr_Duke_0->GetX()[i];
    y_Duke[i] = gr_Duke_0->GetY()[i];
    ye_low_Duke[i] = fabs(gr_Duke_low->Eval(x_Duke[i]) - gr_Duke_0->GetY()[i]);
    ye_high_Duke[i] = fabs(gr_Duke_high->Eval(x_Duke[i]) - gr_Duke_0->GetY()[i]);
  }
  TGraphAsymmErrors *gr_Duke = new TGraphAsymmErrors(gr_Duke_0->GetN(), x_Duke, y_Duke, 0, 0, ye_low_Duke, ye_high_Duke);
  

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

  double x1 = 0.8;
  double x2 = 2.1;
  double y1 = 0.;
  double y2 = 8.;


  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(405);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("T/T_{pc}");
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.045);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(52);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("2#piTD_{s} or 4#pi#eta/s");
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

  TLine *l5 = new TLine(1,1,x2,1);
  l5->SetLineWidth(3);
  l5->SetLineStyle(2);
  l5->Draw("same");


  gr_etaS->SetFillColorAlpha(2,0.50);
  gr_etaS->SetLineColorAlpha(2,0.50);
  gr_etaS->Draw("e3");
  
  gr_etaS_0->SetLineColor(kCyan+2);
  gr_etaS_0->SetLineWidth(4);
  gr_etaS_0->SetLineStyle(1);
  gr_etaS_0->Draw("c");
  
  
  gr_Duke->SetFillColorAlpha(4,0.35);
  gr_Duke->SetLineColorAlpha(4,0.35);
  gr_Duke->Draw("e3");
  
  gr_Duke_0->SetLineColor(kCyan+2);
  gr_Duke_0->SetLineWidth(4);
  gr_Duke_0->SetLineStyle(1);
  gr_Duke_0->Draw("c");

  TLatex *tex = new TLatex(1.75, 4.3, "2#piTD_{s} (charm)");
  tex->SetTextFont(52);
  tex->SetTextSize(0.05);
  tex->SetTextAngle(22);
  tex->Draw("same");

  TLatex *tex = new TLatex(1.8, 1.65, "4#pi#eta/s");
  tex->SetTextFont(52);
  tex->SetTextSize(0.05);
  tex->SetTextAngle(10);
  tex->Draw("same");

  TLatex *tex = new TLatex(0.95, 6.5, "Duke Bayesian");
  tex->SetTextFont(42);
  tex->SetTextSize(0.06);
  tex->Draw("same");
  
  TLatex *tex = new TLatex(1.75, 0.6, "Quantum Limit");
  tex->SetTextFont(22);
  tex->SetTextSize(0.045);
  tex->Draw("same");

  c1->Update();
  c1->SaveAs("fig/D_HQ_etaS_102020.pdf");
  c1->SaveAs("fig/D_HQ_etaS_102020.png");
}
