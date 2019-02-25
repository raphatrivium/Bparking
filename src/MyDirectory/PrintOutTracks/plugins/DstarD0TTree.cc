// system include files
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
//#include "DataFormats/Common/interface/EDProduct.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
//#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Vector.h"

#include <TString.h>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <iostream>
#include "TMath.h"
#include "TTree.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "RecoVertex/KalmanVertexFit/interface/SingleTrackVertexConstraint.h"

//GEN MC Matching
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

//JetCollection (CaloTower) - Gapside
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"

//-------------------------------------------------------------
//#include "DataFormats/CaloTowers/interface/CaloTower.h"
//#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
//--------------------------------------------------------------

//Particle Flow
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//#include "DsD0/DstarD0/interface/EventData.h"
#include "/afs/cern.ch/user/r/ragomesd/TrackingShortExercize/CMSSW_10_2_7/src/MyDirectory/PrintOutTracks/plugins/DstarD0TTree.h"
//#include "DStarD0/DStarD0Analysis/plugins/CastorRecoParaMsRcd.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Utilities/interface/RegexMatch.h"
#include "HLTrigger/HLTanalyzers/plugins/HLTInfo.h"

// L1 related
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTriggerMenuLite.h"

#include "TLorentzVector.h"

using namespace std; 
using namespace reco;
using namespace edm;

DstarD0TTree::DstarD0TTree(const edm::ParameterSet& iConfig):
	doMC(iConfig.getParameter<bool>("doMC")),
	doRec(iConfig.getParameter<bool>("doRec")),
	 
	trkToken_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"))),
	vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("recVtxs"))),
	//genParticlesToken_(consumes<edm::View<reco::GenParticleCollection> >(iConfig.getParameter<edm::InputTag>("genparticles"))),
	//genParticlesTokenDstar_(consumes<GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"))),
    //genParticlesTokenD0_(consumes<GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"))),

	
	comEnergy_(iConfig.getParameter<double>("comEnergy")),
	energyScaleHCAL_(-1.)
	{
		Ebeam_ = comEnergy_/2.;
		edm::Service<TFileService> fs;
		data = fs->make<TTree>("data","data");
	}


DstarD0TTree::~DstarD0TTree()
	{
	 
	   // do anything here that needs to be done at desctruction time
	   // (e.g. close files, deallocate resources etc.)

	}


	//
	// member functions
	//




	// ------------ method called for each event  ------------
void DstarD0TTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	using namespace edm;
	using namespace std;
	using namespace reco;
	pi_mass=0.13957018; k_mass=0.493677;

	  //To clear and initialize variables
	initialize();

	  //run, event, lumi section
	runNumber= iEvent.id().run();
	eventNumber= iEvent.id().event();
	lumi= iEvent.luminosityBlock();

	Handle<double> lumiWeight;
	iEvent.getByLabel("lumiWeight",lumiWeight);

	lumiWeight_=lumi;

	  // Primary Vtx
	  
	edm::Handle<VertexCollection> recVtxs;
	iEvent.getByToken(vtxToken_,recVtxs);


	size_t vtx_trk_size = (*recVtxs)[0].tracksSize();
	int VtxIn=0;
	for(size_t i = 0; i < recVtxs->size(); ++ i)
		{
		const Vertex &vtx = (*recVtxs)[i];
	    	if(vtx.tracksSize()>vtx_trk_size){
	      	VtxIn=i;
	      	vtx_trk_size=vtx.tracksSize();
	    	}
	}

	const Vertex& RecVtx = (*recVtxs)[VtxIn];
	  
	n_pVertex = recVtxs->size();

	PVx = RecVtx.x();
	PVy = RecVtx.y();
	PVz = RecVtx.z();
	PVerrx=RecVtx.xError();
	PVerry=RecVtx.yError();
	PVerrz=RecVtx.zError();

	// Getting tracks from vert(ex)ices

	edm::Handle<TrackCollection> tracks; //access that collection
	iEvent.getByToken(trkToken_,tracks);

	edm::ESHandle<TransientTrackBuilder> theB;
	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
	t_tks = (*theB).build(tracks);

	 //SELECTING TRACKS FOR DSTAR
	for(size_t i=0; i < t_tks.size(); i++)
	{
		TransientTrack t_trk = t_tks.at(i);

		//|dxy| < 0.1 cm, |dz| < 1 cm; χ2 < 2.5, Nhits > 5; pt > 0.15 GeV/c.
		if( fabs(t_trk.track().eta())<2.5 && fabs(t_trk.track().dxy(RecVtx.position()))<0.1 && fabs(t_trk.track().dz(RecVtx.position()))<1. &&
		t_trk.track().normalizedChi2() < 2.5 && t_trk.track().pt() > 0.15)
		{
			slowPiTracks.push_back(&(t_tks.at(i))); //Pion slow candidates Tracks with pt > 0.25 GeV/c

		
			if( (t_trk.track().numberOfValidHits() > 5) && (t_trk.track().pt() > 0.6) )
			{
				goodTracks.push_back(&(t_tks.at(i))); //Pion and kaon candidates Tracks with pt > 0.6 GeV/c
			}
		}

	  	//SELECTING TRACKS FOR D0 ,  χ2 < 5.0, Nhits > 5; pt > 0.15 GeV/c, p > 1.0 GeV/c, |dz| < 0.5 cm; |dxy| < 0.1 cm
		if(fabs(t_trk.track().eta())<2.5 && t_trk.track().normalizedChi2() < 5.0 && t_trk.track().numberOfValidHits() >= 5 && t_trk.track().pt() > 0.5
		&& t_trk.track().p() >1.0 && fabs(t_trk.track().dz(RecVtx.position()))<0.5 && fabs(t_trk.track().dxy(RecVtx.position()))<0.1 )
		{
			goodTracksD0.push_back(&(t_tks.at(i)));
		}

	}

		ntracksDstar = slowPiTracks.size();
        ntracksD0Kpi = goodTracksD0.size();


	    RecDstar(iEvent,iSetup,RecVtx);
	    RecD0(iEvent,iSetup,RecVtx);
	    FindAngle(RecVtx,v_D0,d0kpi_p4);
	    GenDstarInfo(iEvent,iSetup);
		GenD0Info(iEvent,iSetup);
//        FindAngleMCpromptD0(p);
	
		data->Fill();

	}

	void DstarD0TTree::RecDstar(const edm::Event& iEvent, const edm::EventSetup& iSetup, const reco::Vertex& RecVtx){

	using namespace std;
	using namespace reco;
	using namespace edm;
 
	for(size_t i=0;i<goodTracks.size();i++)
	{  
		
		TransientTrack* trk1 = goodTracks.at(i);

		for(size_t j=i+1;j<goodTracks.size();j++)
		{
			    
			TransientTrack* trk2 = goodTracks.at(j);

			if(trk1->charge() == trk2->charge()) continue;

			//Reconstruindo D0 momentum
			math::XYZVector D0fromDstar_p = trk1->track().momentum() + trk2->track().momentum();

			if(sqrt(D0fromDstar_p.perp2()) < 3.) continue; //perp2->transverse component squared

			for(size_t k=0;k<slowPiTracks.size();k++)
			{

				TransientTrack* trkS = slowPiTracks.at(k);
	
				if(*trkS == *trk1 || *trkS == *trk2) continue;

				math::XYZVector DS_p = D0fromDstar_p + trkS->track().momentum();
				if(sqrt(DS_p.perp2())<4.) continue;
	   
				TransientTrack *K=0,*pi=0;

	//COMBINACOES CORRETAS DE CARGAS
				if(trk1->charge() == trkS->charge()){
		  		K = trk2;
				pi = trk1;
					}
				else{
		  		K = trk1;
		 		pi = trk2;
					}		

		//Combinações erradas dcarga - background
	/*
		if(trk1->charge() == trkS->charge()){
		  pi = trk2;
		  K = trk1;
		}
		else{
		  pi = trk1;
		  K = trk2;
		}
	*/
		math::XYZTLorentzVector ip4_K(K->track().px(),K->track().py(),K->track().pz(),sqrt(pow(K->track().p(),2)+pow(k_mass,2)));
		math::XYZTLorentzVector ip4_pi(pi->track().px(),pi->track().py(),pi->track().pz(),sqrt(pow(pi->track().p(),2)+pow(pi_mass,2)));        

		math::XYZTLorentzVector ip4_D0 = ip4_K + ip4_pi;
		
		if( fabs(ip4_D0.M()-1.86484)  > 1.) continue;

		math::XYZTLorentzVector p4_S(trkS->track().px(),trkS->track().py(),trkS->track().pz(),sqrt(pow(trkS->track().p(),2)+pow(pi_mass,2)));
		math::XYZTLorentzVector ip4_DS = ip4_D0 + p4_S;
		if((ip4_DS.M() - ip4_D0.M()) > 0.3) continue;

		// vertexing

		vector<TransientTrack> tks;
		tks.push_back(*K);
		tks.push_back(*pi);
		KalmanVertexFitter kalman(true);
		TransientVertex v = kalman.vertex(tks);
		if(!v.isValid() || !v.hasRefittedTracks()) continue;
		double vtxProb =TMath::Prob( (Double_t) v.totalChiSquared(), (Int_t) v.degreesOfFreedom());
		TransientTrack K_f = v.refittedTrack(*K);
		TransientTrack pi_f = v.refittedTrack(*pi);      


		//D0 from D* Siginificance
		VertexDistanceXY vD0fromDSdXY ;
		double D0fromDSdXY = vD0fromDSdXY.distance(RecVtx,v).value() ;
		double D0fromDSeXY = vD0fromDSdXY.distance(RecVtx,v).error() ;
		double D0fromDSsXY =  D0fromDSdXY / D0fromDSeXY;


		math::XYZTLorentzVector p4_K(K_f.track().px(),K_f.track().py(),K_f.track().pz(),sqrt(pow(K_f.track().p(),2)+pow(k_mass,2)));
		math::XYZTLorentzVector p4_pi(pi_f.track().px(),pi_f.track().py(),pi_f.track().pz(),sqrt(pow(pi_f.track().p(),2)+pow(pi_mass,2)));

		math::XYZTLorentzVector d0_p4 = p4_K + p4_pi;
		double d0mass = d0_p4.M();
		if(fabs(d0mass - 1.86484)>0.2) continue;
		Nd0Cand++;
	   
		math::XYZTLorentzVector dS_p4 = d0_p4 + p4_S;
		double dsmass = dS_p4.M();
		if( (dsmass - d0mass) > 0.16) continue;
		NdsCand++; 

		//Flag
		/*if(doMC){
		
        //edm::Handle<reco::GenParticle> genParticles;
        //iEvent.getByToken("genParticlesToken_",genParticles);
		//  edm::Handle<GenParticleCollection> genParticles;
		//  iEvent.getByToken(genParticlesToken_,genParticles);
        Handle<GenParticleCollection> gens;
        iEvent.getByToken(genParticlesTokenDstar_, gens);	 

		  for(size_t i=0; i<dScandsKpi.size();i++){
		    const GenParticle & ds = gens ->at(dScandsKpi.at(i));
		    double massDS = ds.mass();
		    if (massDS>0) FlagMC=1;
		  }
		}*/
	
	 
		D0_VtxProb.push_back(vtxProb);
		D0mass.push_back(d0_p4.M());
		Dsmass.push_back(dS_p4.M());
		D0pt.push_back(d0_p4.Pt());
		Dspt.push_back(dS_p4.Pt());
		D0eta.push_back(d0_p4.eta());
		D0phi.push_back(d0_p4.phi());
		Dseta.push_back(dS_p4.eta());
		Dsphi.push_back(dS_p4.phi());

		D0_VtxPosx.push_back(v.position().x());
		D0_VtxPosy.push_back(v.position().y());
		D0_VtxPosz.push_back(v.position().z());
		D0_Vtxerrx.push_back(v.positionError().cxx());
		D0_Vtxerry.push_back(v.positionError().cyy());
		D0_Vtxerrz.push_back(v.positionError().czz());

		TrkKdxy.push_back(K_f.track().dxy(RecVtx.position()));
		Trkpidxy.push_back(pi_f.track().dxy(RecVtx.position()));
		TrkSdxy.push_back(trkS->track().dxy(RecVtx.position()));

		TrkKdz.push_back(K_f.track().dz(RecVtx.position()));
		Trkpidz.push_back(pi_f.track().dz(RecVtx.position()));
		TrkSdz.push_back(trkS->track().dz(RecVtx.position()));

		TrkKnhits.push_back(K->track().numberOfValidHits());
		Trkpinhits.push_back(pi->track().numberOfValidHits());
		TrkSnhits.push_back(trkS->track().numberOfValidHits());

		TrkKchi2.push_back(K->track().normalizedChi2());
		Trkpichi2.push_back(pi->track().normalizedChi2());
		TrkSchi2.push_back(trkS->track().normalizedChi2());

		DSDeltaR.push_back(deltaR(d0_p4.eta(),d0_p4.phi(),trkS->track().eta(),trkS->track().phi()));

		TrkKpt.push_back(K_f.track().pt());
		Trkpipt.push_back(pi_f.track().pt());
		TrkSpt.push_back(trkS->track().pt());

		TrkKeta.push_back(K_f.track().eta());
		Trkpieta.push_back(pi_f.track().eta());
		TrkSeta.push_back(trkS->track().eta());

		TrkKphi.push_back(K_f.track().phi());
		Trkpiphi.push_back(pi_f.track().phi());
		TrkSphi.push_back(trkS->track().phi());

		TrkScharge.push_back(trkS->charge());

		D0fromDSsXY_vec.push_back(D0fromDSsXY);     
		
		NKpiCand++;  

		if(NKpiCand>999) break;
	      }
	      if(NKpiCand>999) break;
	    } 
	    if(NKpiCand>999) break;
	  }
}//End RecDstar

	void DstarD0TTree::assignStableDaughters(const reco::Candidate* p, std::vector<int> & pids){

  	for(size_t i=0;i<p->numberOfDaughters();i++){
    if(p->daughter(i)->status()==1)
		pids.push_back(abs(p->daughter(i)->pdgId()));
    	else
    	assignStableDaughters(p->daughter(i),pids);
  	//cout << p->daughter(i)->pdgId() << endl;
	}
  	return;
	}

    //***********************************************************************************
	void DstarD0TTree::GenDstarInfo(const edm::Event& iEvent,const edm::EventSetup& iSetup){
  
    //MC code
  	
 	}
	
    //***********************************************************************************
	void DstarD0TTree::RecD0(const edm::Event& iEvent, const edm::EventSetup& iSetup, const reco::Vertex& RecVtx){

	using namespace edm;
	using namespace std;
	using namespace reco;


	for(size_t i=0;i<goodTracksD0.size();i++){

		TransientTrack* trk1D0 = goodTracksD0.at(i);
		
		for(size_t j=i+1;j<goodTracksD0.size();j++){

			TransientTrack* trk2D0 = goodTracksD0.at(j);
			//Testing charge and if tracks are equal
			if(*trk1D0 == *trk2D0) continue;
			if(trk1D0->charge() == trk2D0->charge()) continue;
			//===============================================
			math::XYZVector D0_p = trk1D0->track().momentum() + trk2D0->track().momentum();
			
			TransientTrack *KfromD0 = 0, *PifromD0 = 0;	

			comb1 = comb2 = false ;
			mass1 = mass2 = 0 ;
			combOR = false;
	
			vD0kaon.SetPtEtaPhiM(trk1D0->track().pt(), trk1D0->track().eta(), trk1D0->track().phi(), k_mass);
			vD0pion.SetPtEtaPhiM(trk2D0->track().pt(), trk2D0->track().eta(), trk2D0->track().phi(), pi_mass);
			vD0_1 = vD0kaon + vD0kaon;
			mass1 = vD0_1.M() + vD0_1.M();
		
			vD0pion.SetPtEtaPhiM(trk1D0->track().pt(), trk1D0->track().eta(), trk1D0->track().phi(), pi_mass);
			vD0kaon.SetPtEtaPhiM(trk2D0->track().pt(), trk2D0->track().eta(), trk2D0->track().phi(), k_mass);
			vD0_2 = vD0kaon + vD0kaon;
            mass2 = vD0_2.M() + vD0_2.M();

			if( fabs(mass1-1.86484) < 1.0) comb1 = true;		
			if( fabs(mass2-1.86484) < 1.0)  comb2 = true;
	
			//====================================
			//If one of the conditions is satisfied	
			if(comb1 || comb2){

				if (comb1){
				KfromD0 = trk1D0; PifromD0 = trk2D0;
				math::XYZVector K_p = trk1D0->track().momentum();
	                     
				vector<TransientTrack> tksD0;
				tksD0.push_back(*KfromD0);
				tksD0.push_back(*PifromD0);
				KalmanVertexFitter kalman(true);
				v_D0 = kalman.vertex(tksD0);
				//TransientVertex v_D0 = kalman.vertex(tksD0);
				if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
				double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
				TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
				TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);      
				//D0 Significance
				VertexDistanceXY vD0KpidXY ;			
				double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
				double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
				double D0KpisXY = D0KpidXY / D0KpieXY;
				//D0 significance 3D
				VertexDistance3D vD0Kpid3D ;
				double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
				double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
				double D0Kpis3D = D0Kpid3D / D0Kpie3D;

				math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
				math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));  
				d0kpi_p4 = p4_KfromD0 + p4_pifromD0;

				double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
				double d0kpimass = d0kpi_p4.M();
				if(fabs(d0kpimass - 1.86484)>0.15) continue;
				ND0KpiCand++;

				double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);

				D0Kpi_VtxProb.push_back(D0KpivtxProb);
				D0Kpimass.push_back(d0kpi_p4.M());
				D0Kpipt.push_back(d0kpi_p4.Pt());
				D0Kpieta.push_back(d0kpi_p4.eta());
				D0Kpiphi.push_back(d0kpi_p4.phi());
		
				D0Kpi_VtxPosx.push_back(v_D0.position().x());
				D0Kpi_VtxPosy.push_back(v_D0.position().y());
				D0Kpi_VtxPosz.push_back(v_D0.position().z());
				D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
				D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
				D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
				D0Kpi_DispAngle.push_back(dispAngle);
				TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
				TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

				TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position())); 
				TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
				TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
				TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
				TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());
		
				TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
				TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
				TrkD0Kpt.push_back(KfromD0_f.track().pt());
				TrkD0pipt.push_back(pifromD0_f.track().pt());
		
				TrkD0Keta.push_back(KfromD0_f.track().eta());
				TrkD0pieta.push_back(pifromD0_f.track().eta());
				TrkD0Kphi.push_back(KfromD0_f.track().phi());
				TrkD0piphi.push_back(pifromD0_f.track().phi());
				D0KpisXY_vec.push_back(D0KpisXY);      
				D0Kpis3D_vec.push_back(D0Kpis3D);
				D0_kT_vec.push_back(D0_kT);

				} // end of combination1

				// -----
			// end of comb1

				if(comb2){
                        	
				KfromD0 = trk2D0; PifromD0 = trk1D0;
				math::XYZVector K_p = trk2D0->track().momentum();

                vector<TransientTrack> tksD0;
                tksD0.push_back(*KfromD0);
                tksD0.push_back(*PifromD0);
                KalmanVertexFitter kalman(true);
                v_D0 = kalman.vertex(tksD0);
                               

                if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
                double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
                TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
                TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);      
				VertexDistanceXY vD0KpidXY ;			
                double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
                double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
                double D0KpisXY = D0KpidXY / D0KpieXY;
				VertexDistance3D vD0Kpid3D ;
                double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
                double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
                double D0Kpis3D = D0Kpid3D / D0Kpie3D;
	
				math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
	        		math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));  
                d0kpi_p4 = p4_KfromD0 + p4_pifromD0;
                double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
                double d0kpimass = d0kpi_p4.M();
                if(fabs(d0kpimass - 1.86484)>0.15) continue;
        			ND0KpiCand++;
	
				double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);

				D0Kpi_VtxProb.push_back(D0KpivtxProb);
                D0Kpimass.push_back(d0kpi_p4.M());
                D0Kpipt.push_back(d0kpi_p4.Pt());
                D0Kpieta.push_back(d0kpi_p4.eta());
                D0Kpiphi.push_back(d0kpi_p4.phi());
		
			 	D0Kpi_VtxPosx.push_back(v_D0.position().x());
                D0Kpi_VtxPosy.push_back(v_D0.position().y());
                D0Kpi_VtxPosz.push_back(v_D0.position().z());
                D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
                D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
                D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
				D0Kpi_DispAngle.push_back(dispAngle);
				TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
                TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));
	
                TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position())); 
                TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
                TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
                TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
                TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());
		
                TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
                TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
                TrkD0Kpt.push_back(KfromD0_f.track().pt());
                TrkD0pipt.push_back(pifromD0_f.track().pt());
		
                TrkD0Keta.push_back(KfromD0_f.track().eta());
				TrkD0pieta.push_back(pifromD0_f.track().eta());
                TrkD0Kphi.push_back(KfromD0_f.track().phi());
                TrkD0piphi.push_back(pifromD0_f.track().phi());
	 			D0KpisXY_vec.push_back(D0KpisXY);      
				D0Kpis3D_vec.push_back(D0Kpis3D);
				D0_kT_vec.push_back(D0_kT);

					} // end of combination 2

				combOR = true;
			} //end of comb1 OR comb 2

			//=============================
			//If both meet the requiremets			
			if(comb1 && comb2 &! combOR){

			if(fabs( mass1-1.864 ) < fabs( mass2-1.864 )){

				KfromD0 = trk1D0; PifromD0 = trk2D0;

                math::XYZVector K_p = trk1D0->track().momentum();

				vector<TransientTrack> tksD0;
                tksD0.push_back(*KfromD0);
                tksD0.push_back(*PifromD0);
                KalmanVertexFitter kalman(true);
                v_D0 = kalman.vertex(tksD0);

                if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
                double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
                TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
                TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);
                VertexDistanceXY vD0KpidXY ;
                double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
                double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
                double D0KpisXY = D0KpidXY / D0KpieXY;
                VertexDistance3D vD0Kpid3D ;
                double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
                double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
                double D0Kpis3D = D0Kpid3D / D0Kpie3D;

                math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
                math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));
                d0kpi_p4 = p4_KfromD0 + p4_pifromD0;
                double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
                double d0kpimass = d0kpi_p4.M();
                if(fabs(d0kpimass - 1.86484)>0.15) continue;
                ND0KpiCand++;

                double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);
				D0Kpi_VtxProb.push_back(D0KpivtxProb);
                D0Kpimass.push_back(d0kpi_p4.M());
                D0Kpipt.push_back(d0kpi_p4.Pt());
                D0Kpieta.push_back(d0kpi_p4.eta());
                D0Kpiphi.push_back(d0kpi_p4.phi());

                D0Kpi_VtxPosx.push_back(v_D0.position().x());
                D0Kpi_VtxPosy.push_back(v_D0.position().y());
                D0Kpi_VtxPosz.push_back(v_D0.position().z());
                D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
                D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
                D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
                D0Kpi_DispAngle.push_back(dispAngle);
                TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
                TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

                TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position()));
                TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
                TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
                TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
                TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());

                TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
                TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
                TrkD0Kpt.push_back(KfromD0_f.track().pt());
                TrkD0pipt.push_back(pifromD0_f.track().pt());

                TrkD0Keta.push_back(KfromD0_f.track().eta());
                TrkD0pieta.push_back(pifromD0_f.track().eta());
                TrkD0Kphi.push_back(KfromD0_f.track().phi());
                TrkD0piphi.push_back(pifromD0_f.track().phi());
                D0KpisXY_vec.push_back(D0KpisXY);
                D0Kpis3D_vec.push_back(D0Kpis3D);
                D0_kT_vec.push_back(D0_kT);

				}

			if(fabs( mass2-1.864 ) < fabs( mass1-1.864 )){
				KfromD0 = trk2D0; PifromD0 = trk1D0;

                math::XYZVector K_p = trk2D0->track().momentum();

                vector<TransientTrack> tksD0;
                tksD0.push_back(*KfromD0);
                tksD0.push_back(*PifromD0);
                KalmanVertexFitter kalman(true);
                v_D0 = kalman.vertex(tksD0);

                if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
                double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
                TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
                TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);
                VertexDistanceXY vD0KpidXY ;
                double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
                double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
                double D0KpisXY = D0KpidXY / D0KpieXY;
                VertexDistance3D vD0Kpid3D ;
                double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
                double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
                double D0Kpis3D = D0Kpid3D / D0Kpie3D;

                math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
                math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));
				d0kpi_p4 = p4_KfromD0 + p4_pifromD0;
                double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
                double d0kpimass = d0kpi_p4.M();
                if(fabs(d0kpimass - 1.86484)>0.15) continue;
                ND0KpiCand++;

                double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);
                D0Kpi_VtxProb.push_back(D0KpivtxProb);
                D0Kpimass.push_back(d0kpi_p4.M());
                D0Kpipt.push_back(d0kpi_p4.Pt());
                D0Kpieta.push_back(d0kpi_p4.eta());
                D0Kpiphi.push_back(d0kpi_p4.phi());

                D0Kpi_VtxPosx.push_back(v_D0.position().x());
                D0Kpi_VtxPosy.push_back(v_D0.position().y());
                D0Kpi_VtxPosz.push_back(v_D0.position().z());
                D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
                D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
                D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
                D0Kpi_DispAngle.push_back(dispAngle);
                TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
                TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

                TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position()));
                TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
                TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
                TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
                TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());

                TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
                TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
                TrkD0Kpt.push_back(KfromD0_f.track().pt());
                TrkD0pipt.push_back(pifromD0_f.track().pt());

                TrkD0Keta.push_back(KfromD0_f.track().eta());
                TrkD0pieta.push_back(pifromD0_f.track().eta());
                TrkD0Kphi.push_back(KfromD0_f.track().phi());
                TrkD0piphi.push_back(pifromD0_f.track().phi());
                D0KpisXY_vec.push_back(D0KpisXY);
                D0Kpis3D_vec.push_back(D0Kpis3D);
                D0_kT_vec.push_back(D0_kT);

				
				}

			 } 
				//end of comb1 AND comb 2


		}

	}

} //END OF RECD0 

    //***********************************************************************************
    void DstarD0TTree::GenD0Info(const edm::Event& iEvent,const edm::EventSetup& iSetup){

    //MC code
    
    }

    //***********************************************************************************
double DstarD0TTree::FindAngle(const reco::Vertex& pv , const TransientVertex& sv, const math::XYZTLorentzVector& vD0angle )
{
   CLHEP::Hep3Vector displacement( sv.position().x() - pv.position().x() , 
                                   sv.position().y() - pv.position().y() , 
                                   sv.position().z() - pv.position().z() ) ; 
   CLHEP::Hep3Vector momentum( vD0angle.Px() , vD0angle.Py() , vD0angle.Pz() ) ; 
   return momentum.angle(displacement) ;
}

/*double DstarD0TTree::FindAngleMCpromptD0(const GenParticle& genD0)
{
   CLHEP::Hep3Vector MCdisplacement( genD0.xProd() - genD0.xDec() ,
                                   genD0.yProd() - genD0.yProd() ,
                                   genD0.zProd() - genD0.zProd() ) ;
   CLHEP::Hep3Vector momentum( genD0.px() , genD0.py() , genD0.pz() ) ;
   return momentum.angle(MCdisplacement) ;	
}*/

//***********************************************************************************
void DstarD0TTree::initialize(){

   dScandsKpi.clear(); goodTracks.clear(); goodTracksD0.clear(); slowPiTracks.clear();
   NKpiCand=0; Nd0Cand=0; NdsCand=0; FlagMC=0; NdsKpiMC=0; 
   PVx = PVy = PVz = PVerrx = PVerry = PVerrz = -999.;
   ntracksD0Kpi = -999; ntracksDstar = -999; n_pVertex = -999; runNumber=0; eventNumber=0; lumi=0; HLTPath_=0; 
   HFEnergyPlus=0.; HFEnergyMinus=0.;  lumiWeight_=0.;
 

   signalpf = false;
     TTBit_32 = 0;
     TTBit_33 = 0;
     TTBit_34 = 0;

     TTBit_8 = 0;
     TTBit_9 = 0;
     TTBit_10 = 0;

   nHFPlus = 0; nHFMinus = 0;

	D0_VtxProb.clear(); D0mass.clear();Dsmass.clear();D0pt.clear();Dspt.clear();D0eta.clear();
    D0phi.clear();Dseta.clear();Dsphi.clear();D0_VtxPosx.clear();D0_VtxPosy.clear();D0_VtxPosz.clear();D0_Vtxerrx.clear(); D0_Vtxerry.clear();
    D0_Vtxerrz.clear();TrkKdxy.clear();Trkpidxy.clear();
    TrkSdxy.clear();TrkKdz.clear();Trkpidz.clear();TrkSdz.clear();
    TrkKnhits.clear();Trkpinhits.clear();TrkSnhits.clear();
    TrkKchi2.clear();Trkpichi2.clear();TrkSchi2.clear();
	DSDeltaR.clear();TrkKpt.clear();Trkpipt.clear();TrkSpt.clear();
    TrkKeta.clear();Trkpieta.clear();TrkSeta.clear();TrkKphi.clear();Trkpiphi.clear();TrkSphi.clear();TrkScharge.clear();
	D0fromDSsXY_vec.clear();

    D0Kpi_VtxProb.clear();D0Kpimass.clear();D0Kpipt.clear();D0Kpieta.clear();
    D0Kpiphi.clear();D0Kpi_VtxPosx.clear();D0Kpi_VtxPosy.clear();
    D0Kpi_VtxPosz.clear();D0Kpi_Vtxerrx.clear();
    D0Kpi_Vtxerry.clear();D0Kpi_Vtxerrz.clear();
    D0Kpi_DispAngle.clear();TrkD0Kdxy.clear();
    TrkD0pidxy.clear();TrkD0Kdz.clear();
    TrkD0pidz.clear();TrkD0Knhits.clear();
    TrkD0pinhits.clear();TrkD0Kchi2.clear();TrkD0pichi2.clear();
    TrkD0Kpt.clear();TrkD0pipt.clear();TrkD0Keta.clear();
    TrkD0pieta.clear();TrkD0Kphi.clear();TrkD0piphi.clear();
	D0KpisXY_vec.clear();
    D0Kpis3D_vec.clear();
	D0_kT_vec.clear();	
//	D0KpisXY_.clear();



   MxFromPFCands_.clear(); EPlusPzFromPFCands_.clear(); EMinusPzFromPFCands_.clear();sumEHFPlusFromPFCands_.clear(); sumEHFMinusFromPFCands_.clear();
   xiPlusFromPFCands_.clear(); xiMinusFromPFCands_.clear(); etaMaxFromPFCands_.clear(); etaMinFromPFCands_.clear(); missingMassFromXiFromPFCands_.clear();
   etaMaxFromPFCandsNew_.clear(); etaMinFromPFCandsNew_.clear();  MCDseta.clear(); MCDsphi.clear(); MCDspt.clear(); MCDsenergy.clear(); MCDsp.clear(); MCDset.clear(); MCDsrapidity.clear(); MCDsmass.clear(); 
   MCDseta.clear(); MCDsphi.clear(); MCDspt.clear(); MCDsenergy.clear(); MCDsp.clear(); MCDset.clear(); MCDsrapidity.clear(); MCDsmass.clear(); 
   MCD0eta.clear(); MCD0phi.clear(); MCD0pt.clear(); MCD0energy.clear(); MCD0p.clear(); MCD0et.clear(); MCD0rapidity.clear(); MCD0mass.clear(); 

   	MCpromptD0eta.clear(); MCpromptD0phi.clear(); MCpromptD0pt.clear(); MCpromptD0energy.clear(); MCpromptD0p.clear(); MCpromptD0et.clear(); MCpromptD0rapidity.clear(); MCpromptD0mass.clear();
   MCpromptD0_Keta.clear(); MCpromptD0_Kphi.clear(); MCpromptD0_Kpt.clear(); MCpromptD0_Kenergy.clear(); MCpromptD0_Kp.clear(); MCpromptD0_Ket.clear(); MCpromptD0_Krapidity.clear(); MCpromptD0_Kmass.clear();
	MCpromptD0_Pieta.clear(); MCpromptD0_Piphi.clear(); MCpromptD0_Pipt.clear(); MCpromptD0_Pienergy.clear(); MCpromptD0_Pip.clear(); MCpromptD0_Piet.clear(); MCpromptD0_Pirapidity.clear(); MCpromptD0_Pimass.clear();

MCpromptD0_DispAngle.clear(); MCpromptD0_Kt.clear();
 /*  xiGenPlus_.clear(); xiGenMinus_.clear(); MxGen_.clear(); MxGenRange_.clear(); sumEnergyHEPlusGen_.clear(); 
   sumEnergyHEMinusGen_.clear(); sumEnergyHFPlusGen_.clear(); MxGenMinus_.clear();
   sumEnergyHFMinusGen_.clear(); etaMaxGen_.clear(); etaMinGen_.clear(); deltaEtaGen_.clear(); etaGapLow_.clear(); etaGapHigh_.clear(); MxGenPlus_.clear();*/

   pfsis1Eta_max.clear(); pfsis2Eta_max.clear(); pfsis1Eta_min.clear(); pfsis2Eta_min.clear(); deltaEtapf.clear();
   
   triggers.clear();

}

//***********************************************************************************
void DstarD0TTree::beginJob(){

data->Branch("Nd0Cand",&Nd0Cand,"Nd0Cand/I");
data->Branch("NdsCand",&NdsCand,"NdsCand/I");
data->Branch("NdsKpiMC",&NdsKpiMC,"NdsKpiMC/I");

data->Branch("runNumber",&runNumber,"runNumber/I");
data->Branch("eventNumber",&eventNumber,"eventNumber/I");
data->Branch("lumi",&lumi,"lumi/I");
data->Branch("lumiWeight_",&lumiWeight_,"lumiWeight_/D");

data->Branch("n_pVertex",&n_pVertex,"n_pVertex/I");
data->Branch("PVx",&PVx,"PVx/D");
data->Branch("PVy",&PVy,"PVy/D");
data->Branch("PVz",&PVz,"PVz/D");
data->Branch("PVerrx",&PVerrx,"PVerrx/D");
data->Branch("PVerry",&PVerry,"PVerry/D");
data->Branch("PVerrz",&PVerrz,"PVerrz/D");
data->Branch("ntracksD0Kpi",&ntracksD0Kpi,"ntracksD0Kpi/I");
data->Branch("ntracksDstar",&ntracksDstar,"ntracksDstar/I");


data->Branch("procId",&procId,"procId/I");

data->Branch("nHFPlus",&nHFPlus,"nHFPlus/I");
data->Branch("nHFMinus",&nHFMinus,"nHFMinus/I");

data->Branch("HLTPath_",&HLTPath_,"HLTPath_/I");


//======================================================
// D0 Variables
//======================================================

data->Branch("D0Kpi_VtxProb",&D0Kpi_VtxProb);
data->Branch("D0Kpimass",&D0Kpimass);
data->Branch("D0Kpipt",&D0Kpipt);
data->Branch("D0Kpieta",&D0Kpieta);
data->Branch("D0Kpiphi",&D0Kpiphi);
data->Branch("D0Kpi_VtxPosx",&D0Kpi_VtxPosx);
data->Branch("D0Kpi_VtxPosy",&D0Kpi_VtxPosy);
data->Branch("D0Kpi_VtxPosz",&D0Kpi_VtxPosz);
data->Branch("D0Kpi_Vtxerrx",&D0Kpi_Vtxerrx);
data->Branch("D0Kpi_Vtxerry",&D0Kpi_Vtxerry);
data->Branch("D0Kpi_Vtxerrz",&D0Kpi_Vtxerrz);
data->Branch("TrkD0Kdxy",&TrkD0Kdxy);
data->Branch("TrkD0pidxy",&TrkD0pidxy);
data->Branch("TrkD0Kdz",&TrkD0Kdz);
data->Branch("TrkD0pidz",&TrkD0pidz);
//data->Branch("TrkD0Kchi2",&TrkD0Kchi2);
//data->Branch("TrkD0pichi2",&TrkD0pichi2);
data->Branch("TrkD0Kpt",&TrkD0Kpt);
data->Branch("TrkD0pipt",&TrkD0pipt);
data->Branch("TrkD0Keta",&TrkD0Keta);
data->Branch("TrkD0pieta",&TrkD0pieta);
data->Branch("TrkD0kphi",&TrkD0Kphi);
data->Branch("TrkD0piphi",&TrkD0piphi);
data->Branch("TrkD0Knhits",&TrkD0Knhits);
data->Branch("TrkD0pinhits",&TrkD0pinhits);
data->Branch("D0KpisXY",&D0KpisXY_vec);
data->Branch("D0Kpis3D",&D0Kpis3D_vec);
data->Branch("D0KpikT",&D0_kT_vec);
data->Branch("D0KpiDispAngle",&D0Kpi_DispAngle);

//======================================================
// D* -> D0 + pi_slow  Variables
//======================================================

data->Branch("D0mass",&D0mass);
data->Branch("Dsmass",&Dsmass);
data->Branch("D0_VtxProb",&D0_VtxProb);
data->Branch("D0_VtxPosx",&D0_VtxPosx);
data->Branch("D0_VtxPosy",&D0_VtxPosy);
data->Branch("D0_VtxPosz",&D0_VtxPosz);
data->Branch("D0_Vtxerrx",&D0_Vtxerrx);
data->Branch("D0_Vtxerry",&D0_Vtxerry);
data->Branch("D0_Vtxerrz",&D0_Vtxerrz);
data->Branch("D0eta",&D0eta);
data->Branch("D0phi",&D0phi);
data->Branch("Dseta",&Dseta);
data->Branch("Dsphi",&Dsphi);
data->Branch("TrkKpt",&TrkKpt);
data->Branch("Trkpipt",&Trkpipt);
data->Branch("TrkSpt",&TrkSpt);
data->Branch("D0pt",&D0pt);
data->Branch("Dspt",&Dspt);
//data->Branch("DSDeltaR",&DSDeltaR);
data->Branch("TrkKnhits",&TrkKnhits);
data->Branch("Trkpinhits",&Trkpinhits);
data->Branch("TrkSnhits",&TrkSnhits);
//data->Branch("TrkKchi2",&TrkKchi2);
//data->Branch("Trkpichi2",&Trkpichi2);
//data->Branch("TrkSchi2",&TrkSchi2);
data->Branch("TrkKdxy",&TrkKdxy);
data->Branch("Trkpidxy",&Trkpidxy);
data->Branch("TrkSdxy",&TrkSdxy);
data->Branch("TrkKdz",&TrkKdz);
data->Branch("Trkpidz",&Trkpidz);
data->Branch("TrkSdz",&TrkSdz);
data->Branch("TrkKeta",&TrkKeta);
data->Branch("Trkpieta",&Trkpieta);
data->Branch("TrkSeta",&TrkSeta);
data->Branch("TrkKphi",&TrkKphi);
data->Branch("Trkpiphi",&Trkpiphi);
data->Branch("TrkSphi",&TrkSphi);
data->Branch("TrkScharge",&TrkScharge);
data->Branch("D0fromDSsXY",&D0fromDSsXY_vec);
data->Branch("triggers",&triggers);

data->Branch("MCDseta",&MCDseta);
data->Branch("MCDsphi",&MCDsphi);
data->Branch("MCDspt",&MCDspt);
data->Branch("MCDsenergy",&MCDsenergy);
data->Branch("MCDsp",&MCDsp);
data->Branch("MCDset",&MCDset);
data->Branch("MCDsrapidity",&MCDsrapidity);
data->Branch("MCDsmass",&MCDsmass);

data->Branch("MCD0eta",&MCD0eta);
data->Branch("MCD0phi",&MCD0phi);
data->Branch("MCD0pt",&MCD0pt);
data->Branch("MCD0energy",&MCD0energy);
data->Branch("MCD0p",&MCD0p);
data->Branch("MCD0et",&MCD0et);
data->Branch("MCD0rapidity",&MCD0rapidity);
data->Branch("MCD0mass",&MCD0mass);

data->Branch("MCpromptD0eta",&MCpromptD0eta);
data->Branch("MCpromptD0phi",&MCpromptD0phi);
data->Branch("MCpromptD0pt",&MCpromptD0pt);
data->Branch("MCpromptD0energy",&MCpromptD0energy);
data->Branch("MCpromptD0p",&MCpromptD0p);
data->Branch("MCpromptD0et",&MCpromptD0et);
data->Branch("MCpromptD0rapidity",&MCpromptD0rapidity);
data->Branch("MCpromptD0mass",&MCpromptD0mass);

data->Branch("MCpromptD0_Keta",&MCpromptD0_Keta);
data->Branch("MCpromptD0_Kphi",&MCpromptD0_Kphi);
data->Branch("MCpromptD0_Kpt",&MCpromptD0_Kpt);
data->Branch("MCpromptD0_Kenergy",&MCpromptD0_Kenergy); 
data->Branch("MCpromptD0_Kp",&MCpromptD0_Kp);
data->Branch("MCpromptD0_Ket",&MCpromptD0_Ket);
data->Branch("MCpromptD0_Krapidity",&MCpromptD0_Krapidity);
data->Branch("MCpromptD0_Kmass",&MCpromptD0_Kmass);

data->Branch("MCpromptD0_Pieta",&MCpromptD0_Pieta);
data->Branch("MCpromptD0_Piphi",&MCpromptD0_Piphi);
data->Branch("MCpromptD0_Pipt",&MCpromptD0_Pipt);
data->Branch("MCpromptD0_Pienergy",&MCpromptD0_Pienergy);
data->Branch("MCpromptD0_Pip",&MCpromptD0_Pip);
data->Branch("MCpromptD0_Piet",&MCpromptD0_Piet);
data->Branch("MCpromptD0_Pirapidity",&MCpromptD0_Pirapidity);
data->Branch("MCpromptD0_Pimass",&MCpromptD0_Pimass);

data->Branch("MCpromptD0_DispAngle",&MCpromptD0_DispAngle);
//data->Branch("MCpromptD0_Kt",&MCpromptD0_Kt);

}

//define this as a plug-in
DEFINE_FWK_MODULE(DstarD0TTree);

