#include "Olympicsa1.h"



Olympics::Olympics(){

}

Olympics::~Olympics(){


}
//all done except from try catch
StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_countryTree->findKey(countryId, this->m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* newCountry = new Country(countryId,medals);
    if(newCountry == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Country>* node = new Node<int,Country>(countryId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->setData(newCountry);
    this->m_countryTree->insertNodeToTree(node,this->m_countryTree->getRoot());
    return StatusType::SUCCESS;
}
//try catch???
StatusType Olympics::remove_country(int countryId){
    if(countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_countryTree->findKey(countryId, this->m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if((this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData()->get_numsContestant() != 0)
       || (this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData()->get_numsTeam() != 0)){
        return StatusType::FAILURE;
    }
    delete this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData();
    this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->setData(nullptr);
    this->m_countryTree->DeleteNodeFromTree(this->m_countryTree->getRoot(),countryId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if (teamId <=0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* curr = m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    Team* newTeam = new Team(teamId,curr,sport);
    if(newTeam == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Team>* node = new Node<int,Team>(teamId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->addOneTeam();
    node->setData(newTeam);
    m_TeamTree->insertNodeToTree(node,m_TeamTree->getRoot());
    return StatusType::SUCCESS;
}


StatusType Olympics::remove_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getNumOfContestant() > 0){
        return StatusType::FAILURE;
    }
    delete m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData();
    m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->setData(nullptr);
    m_TeamTree->DeleteNodeFromTree(m_TeamTree->getRoot(),teamId);
    return StatusType::SUCCESS;
}
//try catchhhhhhh
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || contestantId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* currCountry = m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    Contestant* newContestant = new Contestant(contestantId, currCountry, sport,strength);
    if(newContestant == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Contestant>* node = new Node<int,Contestant>(contestantId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->setData(newContestant);
    m_contestantTree->insertNodeToTree(node,m_contestantTree->getRoot());
    currCountry->addOneContestant();
    return StatusType::SUCCESS;
}
//try catch
StatusType Olympics::remove_contestant(int contestantId){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_contestantTree->findKey(contestantId, m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_numTeam() > 0){
        return StatusType::FAILURE;
    }
    delete (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData());
    m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->setData(nullptr);
    m_contestantTree->DeleteNodeFromTree(m_contestantTree->getRoot(),contestantId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if (contestantId <= 0 || teamId <= 0 ){
        return StatusType::INVALID_INPUT;
    }
    Node<int,Team>* teamNode =  m_TeamTree->findKey(teamId, m_TeamTree->getRoot());
    Node<int,Contestant>* contestantNode = m_contestantTree->findKey(contestantId, m_contestantTree->getRoot());
    if (teamNode == nullptr || contestantNode == nullptr ){
        return StatusType::FAILURE;
    }
    if (teamNode->getData()->getSport() != contestantNode->getData()->get_sport()){
        return StatusType::FAILURE;
    }
    if (teamNode->getData()->getCountry()->get_countryID() != contestantNode->getData()->get_Country()->get_countryID()){
        return StatusType::FAILURE;
    }
    if (contestantNode->getData()->get_numTeam() == THREE ){
        return StatusType::FAILURE;
    }
    for (int i = 0; i < THREE ; ++i) {
        if (contestantNode->getData()->get_teamsArr()[i] == teamId ){
            return StatusType::FAILURE;
        }
    }
    Node<int,Contestant>* contestantNodeToInsert =  new Node<int,Contestant>(contestantId,contestantNode->getData());
   /* StrengthPairKey
    Node<StrengthPairKey,StrengthInfo>* StrengthNodeToInsert =  new Node<StrengthPairKey,StrengthInfo>();

    teamNode->getData()->addContestantToChosenTeam();
*/
    return StatusType::FAILURE;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Node<int,Contestant>* currContestant = m_contestantTree->findKey(contestantId, m_contestantTree->getRoot());
    int oldStrength = currContestant->getData()->get_strength();
    int newStrength = oldStrength + change;
    if (newStrength < 0){
        return StatusType::FAILURE;
    }
    currContestant->getData()->set_strength(newStrength);
    for (int i = 0; i < currContestant->getData()->get_numTeam() ; ++i) {
        Node<int, Team> *teamNode = m_TeamTree->findKey(currContestant->getData()->get_teamsArr()[i],
                                                        m_TeamTree->getRoot());

        StrengthPairKey oldKey = StrengthPairKey(oldStrength, currContestant->getKey());
        StrengthPairKey newKey = StrengthPairKey(newStrength, currContestant->getKey());

        Node<StrengthPairKey, StrengthInfo> *currRootLeft = teamNode->getData()->getRightTreeStrength()->getRoot();
        Node<StrengthPairKey, StrengthInfo> *currRootRight = teamNode->getData()->getRightTreeStrength()->getRoot();
        Node<StrengthPairKey, StrengthInfo> *currRootMiddle = teamNode->getData()->getMiddleTreeStrength()->getRoot();

        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeLeft = teamNode->getData()->getLeftTreeStrength()->findKey(
                oldKey,
                teamNode->getData()->getLeftTreeStrength()->getRoot());
        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeRight = teamNode->getData()->getRightTreeStrength()->findKey(
                oldKey,
                teamNode->getData()->getLeftTreeStrength()->getRoot());
        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeMiddle = teamNode->getData()->getMiddleTreeStrength()->findKey(
                oldKey,
                teamNode->getData()->getLeftTreeStrength()->getRoot());

        Node<StrengthPairKey, StrengthInfo> *newStrengthNode = new Node<StrengthPairKey, StrengthInfo>(newKey,
                                                                                                       currContestant->getData()->getStrengthInfo());
        //looking for the strength in left tree
        if (oldStrengthNodeLeft != nullptr) {
            teamNode->getData()->getLeftTreeStrength()->DeleteNodeFromTree(currRootLeft, oldKey);
            teamNode->getData()->getLeftTreeStrength()->insertNodeToTree(newStrengthNode, currRootLeft);
        }
            //looking for the strength in right tree
        else if (oldStrengthNodeRight != nullptr) {
            teamNode->getData()->getRightTreeStrength()->DeleteNodeFromTree(currRootRight, oldKey);
            teamNode->getData()->getRightTreeStrength()->insertNodeToTree(newStrengthNode, currRootRight);
        }
            //looking for the strength in middle tree
        else if (oldStrengthNodeMiddle != nullptr) {
            teamNode->getData()->getMiddleTreeStrength()->DeleteNodeFromTree(currRootMiddle, oldKey);
            teamNode->getData()->getMiddleTreeStrength()->insertNodeToTree(newStrengthNode, currRootMiddle);
        }
        //update team strength
        teamNode->getData()->setTeamStrength(teamNode->getData()->calcStrength());
    }

    return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId){
    if (contestantId <= 0){
        return StatusType::FAILURE;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_strength();
}

output_t<int> Olympics::get_medals(int countryId){
    if (countryId <= 0){
        return StatusType::FAILURE;
    }
    if (this->m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->get_medals();

}

output_t<int> Olympics::get_team_strength(int teamId){
    if (teamId <= 0){
        return StatusType::FAILURE;
    }
    if (this->m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getTeamStrength();
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    if (m_TeamTree->findKey(teamId1, m_TeamTree->getRoot()) == nullptr || m_TeamTree->findKey(teamId2, m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if(m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getSport() != m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData()->getSport()){
        return StatusType::FAILURE;
    }
    int medalT1 = m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getCountry()->get_medals();
    int medalT2 = m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData()->getCountry()->get_medals();
    int pointTeam1 = medalT1 + get_team_strength(teamId1).ans();
    int pointTeam2 = medalT2 + get_team_strength(teamId1).ans();
    if(medalT1 > medalT1){
        m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getCountry()->addOneTeam();
    }
    if (medalT2 > medalT1){
        m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData()->getCountry()->addOneTeam();
    }
    return StatusType::SUCCESS;
}

output_t<int> Olympics::austerity_measures(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if(  m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getNumOfContestant() < 3){
        return StatusType::FAILURE;
    }

    return 0;
}

