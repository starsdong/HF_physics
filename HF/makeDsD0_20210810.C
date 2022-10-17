#include <stdio.h>
#include "iomanip.h"

void makeDsD0_20210810(const Int_t mPlotTh = 0)
{
  gROOT->Reset();

  const Int_t NConfig = 5;
  const Int_t NMax = 8;
  const Int_t N[NConfig] = {4, 4, 5, 8, 4}; // ALICE_pp, ALICE_PbPb, STAR_AuAu
  const Char_t *ExpName[NConfig] = {"ALICE","ALICE","STAR","CMS","CMS"};
  const Char_t *CollName[NConfig] = {"pp_7TeV","PbPb_30_50_5p02TeV","AuAu_10_40_200GeV","pp_5p02TeV","PbPb_0_100_5p02TeV"};
  double x[NConfig][NMax], y[NConfig][NMax], ye[NConfig][NMax], yes[NConfig][NMax];
  TGraphErrors *gr[NConfig];

  ifstream inData;
  for(int i=0;i<NConfig;i++) {
    inData.open(Form("dat/%s_DsD0_%s.txt",ExpName[i],CollName[i]));
    for(int j=0;j<N[i];j++) {
      inData >> x[i][j] >> y[i][j] >> ye[i][j] >> yes[i][j];
    }
    inData.close();
    gr[i] = new TGraphErrors(N[i], x[i], y[i], 0, ye[i]);
  }
  
  // Theory calculations
  // pythia
  double pt1[100], r1[100];
  int n = 0;
  TFile *fin = new TFile("/Users/starsdong/work/Paper/MINE/HFT_Ds/macros_20190322/root/ALICE_pp7TeV_PbPb5TeV_Pythia.root");
  TGraph *gr_pythia_RHIC_tmp = new TGraph((TH1D *)fin->Get("Pythia_Monash_tune_200GeV"));
  double sum_pt_sub = 0;
  double sum_r_sub = 0;
  int n_sub = 0; // average over 10 GeV/c
  for(int i=0;i<gr_pythia_RHIC_tmp->GetN();i++) {
    double xx = gr_pythia_RHIC_tmp->GetX()[i];
    if(xx<10.0) {
      pt1[n] = xx;
      r1[n] = gr_pythia_RHIC_tmp->GetY()[i];
      n++;
    } else if(xx<15.0){
      sum_pt_sub += gr_pythia_RHIC_tmp->GetX()[i];
      sum_r_sub += gr_pythia_RHIC_tmp->GetY()[i];
      n_sub++;
    }
  }
  pt1[n] = sum_pt_sub/n_sub;
  r1[n] = sum_r_sub/n_sub;
  n++;
  TGraph *gr_pythia_RHIC = new TGraph(n, pt1, r1);
  gr_pythia_RHIC->SetLineWidth(2);
  gr_pythia_RHIC->SetLineColor(2);
  gr_pythia_RHIC->SetFillColor(2);
  gr_pythia_RHIC->Print();

  TGraph *gr_pythia_LHC_tmp = new TGraph((TH1D *)fin->Get("Pythia_Monash_tune_7TeV"));
  double pt2[100], r2[100];
  double sum_pt_sub = 0;
  double sum_r_sub = 0;
  int n = 0;  
  int n_sub = 0; // average over 10 GeV/c
  for(int i=0;i<gr_pythia_LHC_tmp->GetN();i++) {
    double xx = gr_pythia_LHC_tmp->GetX()[i];
    if(xx<10.0) {
      pt2[n] = xx;
      r2[n] = gr_pythia_LHC_tmp->GetY()[i];
      n++;
    } else if(xx<15.0){
      sum_pt_sub += gr_pythia_LHC_tmp->GetX()[i];
      sum_r_sub += gr_pythia_LHC_tmp->GetY()[i];
      n_sub++;
    }
  }
  pt2[n] = sum_pt_sub/n_sub;
  r2[n] = sum_r_sub/n_sub;
  n++;
  TGraph *gr_pythia_LHC = new TGraph(n, pt2, r2);
  gr_pythia_LHC->SetLineWidth(2);
  gr_pythia_LHC->SetLineColor(1);
  gr_pythia_LHC->SetFillColor(1);
  gr_pythia_LHC->Print();
  

  // TFile *fin = new TFile("root/pythia_D_ratio.root");
  // TGraphErrors *gr_pythia = (TGraphErrors *)fin->Get("Ratio_Ds_D0");
  // gr_pythia->SetLineWidth(2);
  // gr_pythia->SetLineColor(8);

  // TFile *fin = new TFile("root/PYTHIA8_D_ratio_7TeV_20181029_0.root");
  // TDirectoryFile *fDs = (TDirectoryFile *)fin->Get("Ds");
  // TH1D *h_pythia8 = (TH1D *)fDs->Get("DstoD0_pt_whole_rebin");
  // TGraph *gr_pythia8 = new TGraph(h_pythia8);
  // gr_pythia8->SetLineWidth(1);
  // gr_pythia8->SetLineStyle(1);

  /*
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
  */  
  

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
  c1->SetTickx();
  c1->SetTicky();
  c1->Draw();
  c1->cd();


  double x1 = 0.01;
  double x2 = 16.0;
  double y1 = 0.;
  double y2 = 0.75;
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
  h0->GetYaxis()->SetTitle("D_{s}^{+}/D^{0}");
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

  gr_pythia_RHIC->Draw("c");
  gr_pythia_LHC->Draw("c");

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
  const Int_t kStyle[NConfig] = {25, 21, 20, 26, 22};
  const Int_t kColor[NConfig] = {1, 1, 2, 4, 4};
  const Double_t size[NConfig] = {2.0, 2.2, 2.2, 2.0, 2.5};
  const double xo = fabs(x2-x1)/100.;
  const double yo = fabs(y2-y1)/100.;
  for(int i=0;i<NConfig;i++) {

    for(int j=0;j<N[i];j++) {
      double x1 = x[i][j] - xo;
      double x2 = x[i][j] + xo;
      double y1 = y[i][j] - yes[i][j];
      double y2 = y[i][j] + yes[i][j];
      
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
    gr[i]->SetMarkerSize(size[i]);
    gr[i]->SetLineColor(kColor[i]);
    gr[i]->SetLineWidth(2);
    gr[i]->Draw("p");
  }
  

   TLegend *leg = new TLegend(0.18, 0.72, 0.54, 0.95);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.03);
   leg->AddEntry(gr[2], " STAR Au+Au@200GeV, 10-40%", "pl");
   leg->AddEntry(gr[1], " ALICE Pb+Pb@5.02TeV, 30-50%", "pl");
   leg->AddEntry(gr[4], " CMS Pb+Pb@5.02TeV, 0-100%", "pl");
   leg->AddEntry(gr[0], " ALICE p+p@7TeV", "pl");
   leg->AddEntry(gr[3], " CMS p+p@5.02TeV", "pl");
   leg->Draw();
  
   TLegend *leg = new TLegend(0.6, 0.16, 0.94, 0.26);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.03);
   leg->AddEntry(gr_pythia_LHC, " PYTHIA8 @7TeV", "l");
   leg->AddEntry(gr_pythia_RHIC, " PYTHIA8 @200GeV", "l");
   leg->Draw();

   c1->Update();
  c1->cd();
  
  c1->SaveAs("fig/DsD0Ratio_20210810.pdf");
  c1->SaveAs("fig/DsD0Ratio_20210810.png");
  
  
}
