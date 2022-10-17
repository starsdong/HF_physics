#include "style.C+"
#include "draw.C+"

void makeCharmRatio(const bool SHM = true)
{
  style();
  const Int_t NP = 4;
  const Double_t fr[NP] = {0.568, 0.240, 0.100, 0.082};
  const Double_t Xsec[NP] = {39.0, 20.7, 15.4, 36.4};
  const Double_t Xsec_e[NP] = {1.2, 4.0, 4.0, 22.9};
  const Char_t *Title[NP-1] = {"D^{+}/D^{0}", "D_{s}^{+}/D^{0}", "#Lambda_{c}^{+}/D^{0}"};

  Double_t xx[NP-1], r_pp[NP-1], r_AA[NP-1], re_AA[NP-1];
  for(int i=0;i<NP-1;i++) {
    xx[i] = i+0.5;
    r_pp[i] = fr[i+1]/fr[0];
    r_AA[i] = Xsec[i+1]/Xsec[0];
    re_AA[i] = Xsec_e[i+1]/Xsec[0];
  }

  // SHM model prediction - Rapp
  Double_t r_SHM_h[NP-1] = {0.45, 0.363, 0.570};  
  Double_t r_SHM_l[NP-1] = {0.44, 0.352, 0.441};

  TGraphErrors *gr_AA = new TGraphErrors(NP-1, xx, r_AA, 0, re_AA);
  gr_AA->SetMarkerStyle(20);
  gr_AA->SetMarkerSize(1.5);
  gr_AA->SetLineWidth(2);

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetLogy();
  c1->Draw();

  TH1D *h0 = new TH1D("h0","",1,0,3);
  h0->SetMinimum(0.05);
  h0->SetMaximum(2.5);
  h0->GetXaxis()->SetTitle("");
  h0->GetXaxis()->SetNdivisions(301);
  h0->GetXaxis()->SetLabelOffset(999.);
  h0->GetXaxis()->SetTitleOffset(999.);
  h0->GetYaxis()->SetTitle("Ratio to D^{0}");
  h0->GetYaxis()->SetNdivisions(302);
  h0->Draw();

  TLine *l_pp[NP-1];
  TBox *b_SHM[NP-1];
  const Double_t x_offset = 0.2;
  for(int i=0;i<NP-1;i++) {
    b_SHM[i] = new TBox(xx[i]-x_offset, r_SHM_l[i], xx[i]+x_offset, r_SHM_h[i]);
    b_SHM[i]->SetFillColor(kGreen+2);
    b_SHM[i]->SetLineColor(kGreen+2);
    if(SHM) b_SHM[i]->Draw("same");

    l_pp[i] = new TLine(xx[i]-x_offset, r_pp[i], xx[i]+x_offset, r_pp[i]);
    l_pp[i]->SetLineWidth(3);
    l_pp[i]->Draw("same");
  }

  gr_AA->Draw("p");

  TLegend *leg0 = new TLegend(0.25, 0.85, 0.4, 0.95);
  leg0->SetFillColor(10);
  leg0->SetFillStyle(10);
  leg0->SetLineStyle(4000);
  leg0->SetLineColor(10);
  leg0->SetLineWidth(0.);
  leg0->SetTextSize(0.05);
  leg0->AddEntry(gr_AA, " STAR Au+Au #sqrt{s_{NN}} = 200 GeV", "p");
  leg0->Draw();
  
  TLegend *leg1;
  if(SHM) leg1 = new TLegend(0.25, 0.2, 0.6, 0.36);
  else leg1 = new TLegend(0.25, 0.2, 0.6, 0.28);
  leg1->SetFillColor(10);
  leg1->SetFillStyle(10);
  leg1->SetLineStyle(4000);
  leg1->SetLineColor(10);
  leg1->SetLineWidth(0.);
  leg1->SetTextSize(0.05);
  if(SHM) leg1->AddEntry(b_SHM[0], " SHM", "f");
  leg1->AddEntry(l_pp[0], " PYTHIA", "l");
  leg1->Draw();

  TLatex *tex[NP-1];
  for(int i=0;i<NP-1;i++) {
    tex[i] = new TLatex(i+0.3, 0.03, Title[i]);
    //    tex[i]->SetTextAngle(90);
    tex[i]->SetTextSize(0.07);
    tex[i]->SetTextFont(42);
    tex[i]->Draw("same");
  }

  c1->Update();
  c1->SaveAs(Form("fig/charmRatio_%d.pdf",SHM));
  c1->SaveAs(Form("fig/charmRatio_%d.png",SHM));
}

