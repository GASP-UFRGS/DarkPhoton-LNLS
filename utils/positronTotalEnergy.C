void positronTotalEnergy()
{
    TCanvas *c1 = new TCanvas("c2", "c2");

    TFile *input = new TFile("output.root", "read");

    TTree *tree = (TTree*)input->Get("PositronHits");

    int EventID;
    double PositronEnergy, positronx, positronY;

    tree->SetBranchAddress("PositronEnergy", &PositronEnergy);
    tree->SetBranchAddress("EventID", &EventID);

    int entries = tree->GetEntries();

    //cout << entries << endl;

    TH1F *hist = new TH1F("hist", "PositronEnergy", 200, 549.5, 550); //name, title, n_bins, range1, range2

    for(int i = 0; i < entries; i++) {
	tree->GetEntry(i);

	cout << PositronEnergy << " " << EventID << endl;

	hist->Fill(PositronEnergy);
    }

    hist->Draw();

    c1->SaveAs("positronHisto.png");

    input->Close();
}

