#include <stdio.h>
#include "iomanip.h"

void makeDsD0_20_40()
{
  gROOT->Reset();

  const Int_t NConfig = 1;
  const Int_t NMax = 8;
  const Int_t N[NConfig] = {4}; // STAR_AuAu
  const Char_t *ExpName[NConfig] = {"STAR"};
  const Char_t *CollName[NConfig] = {"AuAu_20_40_200GeV"};
  double x[NConfig][NMax], y[NConfig][NMax], ye[NConfig][NMax], yesl[NConfig][NMax], yesu[NConfig][NMax];
  TGraphErrors *gr[NConfig];
  //  TGraphAsymmErrors *gr_sys[NConfig];

  ifstream inData;
  for(int i=0;i<NConfig;i++) {
    inData.open(Form("dat/%s_DsD0_%s.txt",ExpName[i],CollName[i]));
    for(int j=0;j<N[i];j++) {
      inData >> x[i][j] >> y[i][j] >> ye[i][j] >> yesl[i][j] >> yesu[i][j];
    }
    inData.close();
    gr[i] = new TGraphErrors(N[i], x[i], y[i], 0, ye[i]);
    //    gr_sys[i] = new TGraphAsymmErrors(N[i], x[i], y[i], 0, 0, yesl[i], yesu[i]);
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
  gr_pythia_RHIC->SetLineColor(kGreen+2);
  gr_pythia_RHIC->SetFillColor(kGreen+2);
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
  


  TGraph *gr_Tsinghua = new TGraph("dat/Tsinghua_DsD0_AuAu200GeV_20_40.txt","%lg %lg");
  gr_Tsinghua->SetLineColor(2);
  gr_Tsinghua->SetLineWidth(2);
  gr_Tsinghua->SetLineStyle(9);
  

  TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
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
  c1->SetBottomMargin(0.16);
  c1->SetTickx();
  c1->SetTicky();
  c1->Draw();
  c1->cd();


  double x1 = 0.01;
  double x2 = 8.0;
  double y1 = 0.;
  double y2 = 0.75;
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(104);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(1.1);
  h0->GetXaxis()->SetTitleSize(0.06);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.06);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(105);
  h0->GetYaxis()->SetTitle("(D_{s}^{+}+D_{s}^{-})/(D^{0}+#bar{D}^{0})");
  h0->GetYaxis()->SetTitleOffset(1.1);
  h0->GetYaxis()->SetTitleSize(0.06);
  h0->GetYaxis()->SetLabelOffset(0.01);
  h0->GetYaxis()->SetLabelSize(0.06);
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
  //  gr_pythia_LHC->Draw("c");
  gr_Tsinghua->Draw("c");

  // plotting the data points
  const Int_t kStyle[NConfig] = {24};
  const Int_t kColor[NConfig] = {1};
  const Double_t size[NConfig] = {3.0};
  const double xo = fabs(x2-x1)/100.;
  const double yo = fabs(y2-y1)/100.;
  for(int i=0;i<NConfig;i++) {

    for(int j=0;j<N[i];j++) {
      double x1 = x[i][j] - xo;
      double x2 = x[i][j] + xo;
      double y1 = y[i][j] - yesl[i][j];
      double y2 = y[i][j] + yesu[i][j];

      TBox *box = new TBox(x1, y1, x2, y2);
      box->SetFillColor(16);
      box->SetLineColor(16);
      box->Draw("same");
      
      // TLine *la = new TLine(x1, y1, x1, y1+yo);
      // la->SetLineColor(kColor[i]);
      // la->SetLineWidth(1);
      // la->Draw("same");
      // TLine *lb = new TLine(x2, y1, x2, y1+yo);
      // lb->SetLineColor(kColor[i]);
      // lb->SetLineWidth(1);
      // lb->Draw("same");
      // TLine *lc = new TLine(x1, y2, x1, y2-yo);
      // lc->SetLineColor(kColor[i]);
      // lc->SetLineWidth(1);
      // lc->Draw("same");
      // TLine *ld = new TLine(x2, y2, x2, y2-yo);
      // ld->SetLineColor(kColor[i]);
      // ld->SetLineWidth(1);
      // ld->Draw("same");
      // TLine *le = new TLine(x1, y1, x2, y1);
      // le->SetLineColor(kColor[i]);
      // le->SetLineWidth(2);
      // le->Draw("same");
      // TLine *lf = new TLine(x1, y2, x2, y2);
      // lf->SetLineColor(kColor[i]);
      // lf->SetLineWidth(2);
      // lf->Draw("same");
    }

    TGraph *gr_tmp = gr[0]->Clone();
    gr_tmp->SetMarkerStyle(20);
    gr_tmp->SetMarkerColor(2);
    gr_tmp->SetMarkerSize(2.8);
    gr_tmp->Draw("p");

    
    gr[i]->SetMarkerStyle(kStyle[i]);
    gr[i]->SetMarkerColor(kColor[i]);
    gr[i]->SetMarkerSize(size[i]);
    gr[i]->SetLineColor(kColor[i]);
    gr[i]->SetLineWidth(3);
    gr[i]->Draw("p");
  }


  TLatex *tex = new TLatex(0.6, 0.65, "Au+Au, #sqrt{s_{NN}} = 200 GeV, 20-40%");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->Draw("same");
  
  
   TLegend *leg = new TLegend(0.65, 0.18, 0.94, 0.32);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.05);
   leg->AddEntry(gr_Tsinghua, " Tsinghua","l");
   leg->AddEntry(gr_pythia_RHIC, " PYTHIA", "l");
   leg->Draw();

   c1->Update();
  c1->cd();
  
  c1->SaveAs("fig/DsD0Ratio_20_40.pdf");
  c1->SaveAs("fig/DsD0Ratio_20_40.png");
  
  
}
