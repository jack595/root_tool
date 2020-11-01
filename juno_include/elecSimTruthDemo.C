#include "Event/ElecHeader.h"
#include "Event/ElecTruthHeader.h"
#include "Context/TimeStamp.h"
#include "TFile.h"
#include "TTree.h"
void elecSimTruthDemo()
{
  // TFile* f = new TFile("/junofs/production/data-production/Pre-Releases/J19v1r0-Pre3/Laser/center/photon_22000/elecsim/elecsim-1100.root", "read");
  // TFile* f = new TFile("/junofs/production/data-production/Pre-Releases/J19v1r0-Pre3/ACU/Co60/Co60_0_0_17000/elecsim/elecsim-13400.root", "read");
  // TFile* f = new TFile("/junofs/production/data-production/Pre-Releases/J19v1r0-Pre3/C14/C14/elecsim/elecsim-100.root", "read");
  // TFile* f = new TFile("/junofs/production/data-production/Pre-Releases/J19v1r0-Pre3/ACU/AmC/AmC_0_0_17000/elecsim/elecsim-43400.root", "read");
  // TFile* f = new TFile("/junofs/users/zhangxt/20inch/rec/deconvolution/runs/20200331sample/Ge68/C14_0/elecsim/elecsim-1000.root", "read");


  TFile* f = new TFile("/junofs/users/huangx/production/J20v1r0-Pre0/CLS/AmC/AmC_0_0_-10000/elecsim/elecsim-100600.root", "read");
  TTree* tElec = (TTree*)f->Get("Event/Elec/ElecEvent");
  TTree* tTruth = (TTree*)f->Get("Event/Sim/Truth/LpmtElecTruthEvent");
  JM::ElecEvent* ee = new JM::ElecEvent();
  JM::LpmtElecTruthEvent* et = new JM::LpmtElecTruthEvent();
  tElec->SetBranchAddress("ElecEvent", &ee);
  tTruth->SetBranchAddress("LpmtElecTruthEvent", &et);
  cout << "Total Elec Events: " << tElec->GetEntries() << endl;
  cout << "Total ElecTruth Events: " << tTruth->GetEntries() << endl;
  if (tElec->GetEntries() != tTruth->GetEntries()) cout << "Wrong input data, please check!" << endl;

  // for (int i = 0; i < tElec->GetEntries(); i++) {
  for (int i = 0; i < 1; i++) {
    tElec->GetEntry(i);
    tTruth->GetEntry(i);

    // read elecsim waveform
    const JM::ElecFeeCrate& efc = ee->elecFeeCrate();
    JM::ElecFeeCrate* m_crate;
    m_crate = const_cast<JM::ElecFeeCrate*>(&efc);
    std::map<int, JM::ElecFeeChannel>* feeChannels = &m_crate->channelData();
    // std::map<int, JM::ElecFeeChannel> &feeChannels = (m_crate->channelData());
    std::map<int, JM::ElecFeeChannel>::iterator it;
    // for (it = feeChannels.begin(); it != feeChannels.end(); ++it) {
    for (it = feeChannels->begin(); it != feeChannels->end(); ++it) {
      JM::ElecFeeChannel& channel = (it->second);
      if (channel.adc().size() == 0) continue;
      cout << channel.adc().at(0) << endl;
      int pmtID = it->first;
    }

    // read elecsim truth
    const std::vector<JM::LpmtElecTruth>& let = et->truths();
    std::vector<JM::LpmtElecTruth>* m_truths;
    m_truths = const_cast<std::vector<JM::LpmtElecTruth>*>(&let);
    cout << m_truths->size() << endl;
    for (int j = 0; j < m_truths->size(); j++) {
      std::string m_pulsetype = m_truths->at(j).pulsetype();      // sourse type of the pulse('tag' setting  by user, DN, AP or Unknow)
      int m_pmtId = m_truths->at(j).pmtId();                      // pmt id of the pulse
      int m_npe = m_truths->at(j).npe();                          // photon-electron number of the pulse
      double m_hitTime = m_truths->at(j).hitTime();               // hit time as from detector simulation
      double m_amplitude = m_truths->at(j).amplitude();           // amplitude as from PMT simulation
      double m_TTS = m_truths->at(j).tts();                       // transit time of the hit
      double m_timeoffset = m_truths->at(j).timeoffset();         // time offset of the hit
      TimeStamp m_pulseHitTime = m_truths->at(j).pulseHitTime();  // TimeStamp of the pulse = event time stamp + transit time + time offset
                                                                  // if (i < 1) {
                                                                  // cout << "pulse type: " << m_pulsetype.c_str() << endl;
                                                                  // cout << "pmtID: " << m_pmtId << endl;
                                                                  // cout << "nPE: " << m_npe << endl;
                                                                  // cout << "hit time: " << m_hitTime << endl;
                                                                  // cout << "amplitude: " << m_amplitude << endl;
                                                                  // cout << "TTS: " << m_TTS << endl;
                                                                  // cout << "time offset: " << m_timeoffset << endl;
                                                                  // cout << endl;
                                                                  //}
    }
  }
}
