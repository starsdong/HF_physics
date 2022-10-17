#include <stdio.h>
#include "iomanip.h"

void makeLcD0_20191107(const Int_t mPlotTh = 0)
{
  gROOT->Reset();

  const Int_t NConfig = 4;
  const Int_t NMax = 5;
  const Int_t N[NConfig] = {5, 4, 5, 3}; // ALICE_pp, ALICE_pPb, STAR_AuAu
  const Char_t *ExpName[NConfig] = {"ALICE","ALICE","ALICE", "STAR"};
  const Char_t *CollName[NConfig] = {"pp_7TeV","pPb_5p02TeV","PbPb_0_10_5p02TeV","AuAu_10_80_200GeV"};
  double x[NConfig][NMax], y[NConfig][NMax], ye[NConfig][NMax], yes_u[NConfig][NMax], yes_d[NConfig][NMax];
  TGraphErrors *gr[NConfig];

  ifstream inData;
  for(int i=0;i<NConfig;i++) {
    inData.open(Form("dat/%s_LcD0_%s.txt",ExpName[i],CollName[i]));
    for(int j=0;j<N[i];j++) {
      inData >> x[i][j] >> y[i][j] >> ye[i][j] >> yes_u[i][j] >> yes_d[i][j];
    }
    inData.close();
    gr[i] = new TGraphErrors(N[i], x[i], y[i], 0, ye[i]);
    cout << Form("dat/%s_LcD0_%s.txt",ExpName[i],CollName[i]) << endl;
    gr[i]->Print();
  }
  
  // Theory calculations
  // pythia
  TFile *fin = new TFile("root/pythia_D_ratio.root");
  TGraphErrors *gr_pythia_tmp = (TGraphErrors *)fin->Get("Ratio_Lc_D0");
  TGraph *gr_pythia = new TGraph(*gr_pythia_tmp);
  gr_pythia->SetLineWidth(2);
  gr_pythia->SetLineColor(kGreen+4);

  TFile *fin = new TFile("root/PYTHIA8_D_ratio_200GeV_20191101_CR.root");
  TGraphErrors *gr_pythia_CR_tmp = (TGraphErrors *)fin->Get("gLc2D0");
  TGraph *gr_pythia_CR = new TGraph(*gr_pythia_CR_tmp);
  gr_pythia_CR->SetLineWidth(2);
  gr_pythia_CR->SetLineStyle(7);
  gr_pythia_CR->SetLineColor(kGreen+4);
  
  const Int_t N_Greco = 14;
  Double_t pt_Greco[N_Greco], y_Greco[N_Greco], ye_Greco[N_Greco];
  inData.open("dat/LcD0_Greco_1407.5069.txt");
  for(int i=0;i<N_Greco;i++) {
    double a, b, c;
    inData >> a >> b >> c;
    pt_Greco[i] = a;
    y_Greco[i] = (b+c)/2.;
    ye_Greco[i] = fabs(b-c)/2.;
  }
  inData.close();
  TGraphErrors *gr_Greco = new TGraphErrors(N_Greco, pt_Greco, y_Greco, 0, ye_Greco);
  gr_Greco->SetFillColor(16);
  gr_Greco->SetLineColor(16);

  const Int_t N_Ko = 12;
  Double_t pt_Ko[N_Ko], y1_Ko[N_Ko], y2_Ko[N_Ko], y3_Ko[N_Ko];
  inData.open("dat/LcD0_Ko_0901.1382.txt");
  for(int i=0;i<N_Ko;i++) {
    inData >> pt_Ko[i] >> y1_Ko[i] >> y2_Ko[i] >> y3_Ko[i];
  }
  inData.close();
  TGraph *gr_Ko_1 = new TGraph(N_Ko, pt_Ko, y1_Ko);
  gr_Ko_1->SetLineWidth(2);
  gr_Ko_1->SetLineStyle(2);
  TGraph *gr_Ko_2 = new TGraph(N_Ko, pt_Ko, y2_Ko);
  gr_Ko_2->SetLineWidth(2);
  gr_Ko_2->SetLineStyle(3);
  TGraph *gr_Ko_3 = new TGraph(N_Ko, pt_Ko, y3_Ko);
  gr_Ko_3->SetLineWidth(2);
  gr_Ko_3->SetLineStyle(4);
  
  

  TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,800);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  c1->SetFillColor(10);
  c1->SetFillStyle(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(0);
  c1->SetFrameFillColor(10);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.14);
  c1->SetRightMargin(0.03);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.14);
  // c1->SetTickx();
  // c1->SetTicky();
  c1->Draw();
  c1->cd();


  double x1 = 0.01;
  double x2 = 10.9;
  double y1 = 0.;
  double y2 = 1.8;
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(208);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(1.1);
  h0->GetXaxis()->SetTitleSize(0.055);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.035);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("#Lambda_{c}/D^{0}");
  h0->GetYaxis()->SetTitleOffset(1.2);
  h0->GetYaxis()->SetTitleSize(0.055);
  h0->GetYaxis()->SetLabelOffset(0.01);
  h0->GetYaxis()->SetLabelSize(0.035);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(42);
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


  gr_pythia->Draw("c");
  gr_pythia_CR->Draw("c");

  
  if(mPlotTh) {
  gr_Greco->Draw("e3");
  gr_Ko_1->Draw("c");
  gr_Ko_2->Draw("c");
  gr_Ko_3->Draw("c");

  TLatex *tex = new TLatex(3, 0.32, "Greco");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");

  TLatex *tex = new TLatex(1, 0.78, "Ko: three-quark");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");

  TLatex *tex = new TLatex(2, 1.3, "Ko: di-quark");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");

  TLine *la = new TLine(0.2, 0.24, 1.5, 0.24);
  la->SetLineWidth(5);
  la->SetLineColor(18);
  la->Draw("same");

  TLatex *tex = new TLatex(0.5, 0.26, "SHM");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");
  }

  // plotting the data points
  const Int_t kStyle[NConfig] = {25, 26, 21, 20};
  const Int_t kColor[NConfig] = {1, 1, 1, 2};
  const Double_t kSize[NConfig] = {2.0, 2.0, 2.0, 2.5};
  const double xo = fabs(x2-x1)/100.;
  const double yo = fabs(y2-y1)/100.;
  for(int i=0;i<NConfig;i++) {

    if(i==1) continue; // skipe pPb
    for(int j=0;j<N[i];j++) {
      double x1 = x[i][j] - xo;
      double x2 = x[i][j] + xo;
      double y1 = y[i][j] - yes_d[i][j];
      double y2 = y[i][j] + yes_u[i][j];
      
      TLine *la = new TLine(x1, y1, x1, y1+yo);
      la->SetLineColor(kColor[i]);
      la->SetLineWidth(1);
      la->Draw("same");
      TLine *lb = new TLine(x2, y1, x2, y1+yo);
      lb->SetLineColor(kColor[i]);
      lb->SetLineWidth(1);
      lb->Draw("same");
      TLine *lc = new TLine(x1, y2, x1, y2-yo);
      lc->SetLineColor(kColor[i]);
      lc->SetLineWidth(1);
      lc->Draw("same");
      TLine *ld = new TLine(x2, y2, x2, y2-yo);
      ld->SetLineColor(kColor[i]);
      ld->SetLineWidth(1);
      ld->Draw("same");
      TLine *le = new TLine(x1, y1, x2, y1);
      le->SetLineColor(kColor[i]);
      le->SetLineWidth(2);
      le->Draw("same");
      TLine *lf = new TLine(x1, y2, x2, y2);
      lf->SetLineColor(kColor[i]);
      lf->SetLineWidth(2);
      lf->Draw("same");
    }
    gr[i]->SetMarkerStyle(kStyle[i]);
    gr[i]->SetMarkerColor(kColor[i]);
    gr[i]->SetMarkerSize(kSize[i]);
    gr[i]->SetLineColor(kColor[i]);
    gr[i]->SetLineWidth(2);
    gr[i]->Draw("p");
  }
  

   TLegend *leg = new TLegend(0.40, 0.80, 0.94, 0.95);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.032);
   leg->AddEntry(gr[3], " STAR Au+Au@200GeV, 10-80%", "pl");
   leg->AddEntry(gr[2], " ALICE Pb+Pb@5.02TeV, 0-10%", "pl");
   leg->AddEntry(gr[0], " ALICE p+p@7TeV", "pl");
   leg->Draw();
  
   TLegend *leg = new TLegend(0.50, 0.68, 0.94, 0.78);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.032);
   leg->AddEntry(gr_pythia_CR, " PYTHIA CR @200GeV", "l");
   leg->AddEntry(gr_pythia, " PYTHIA @200GeV", "l");
   leg->Draw();

   c1->Update();
  c1->cd();
  
  c1->SaveAs("fig/LcD0Ratio_20191107.pdf");
  c1->SaveAs("fig/LcD0Ratio_20191107.png");
  
  
}
