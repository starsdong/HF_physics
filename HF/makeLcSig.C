void makeLcSig()
{
  gROOT->Reset();
  gROOT->LoadMacro("~/work/work/fitfun/GaussFunctions.C");
  
  const Int_t NMax = 100;
  double m[NMax], c[NMax], c_err[NMax];
  
  TGraph *gr = new TGraph("dat/Lc_PbPb_1809.10922.txt","%lg %lg");
  int n = gr->GetN();
  for(int i=0;i<n;i++) {
    m[i] = gr->GetX()[i];
    c[i] = gr->GetY()[i];
    c_err[i] = sqrt(c[i]);
  }
  TGraphErrors *gr_m = new TGraphErrors(n, m, c, 0, c_err);

  double x1 = 2.155;
  double x2 = 2.425;
  double y1 = 12400.;
  double y2 = 15400.;
  
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle("Mass");
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(210);
   d0->GetYaxis()->SetTitle("Counts");
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

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
  
   gr_m->SetMarkerStyle(20);
   gr_m->SetMarkerSize(1.5);
   gr_m->SetLineWidth(2);
   gr_m->Draw("p");

   TF1 *fun = new TF1("fun",GaussQuadratic,x1,x2,6);
   fun->SetParameters(10.,2.286,0.014,13000.,0.,0.);
   fun->FixParameter(2,0.014);

   TF1 *fun1 = new TF1("fun1","pol4",x1,x2);
   fun1->SetParameters(13000.,0.,0.,0.,0.);

   //   gr_m->Fit("fun","R");
}
