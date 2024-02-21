#include "Olympicsa1.h"



Olympics::Olympics(){

}

Olympics::~Olympics(){


}

StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_countryTree->m_root->findKey(countryId) == nullptr){
        return StatusType::FAILURE;
    }
    Country* newCountry = new Country(countryId,medals);
    if(newCountry == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<Country>* node = new Node<Country>(countryId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->data = newCountry;
    this->m_countryTree->m_root->insertNode(node);
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_country(int countryId){
    if(countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_countryTree->m_root->findKey(countryId) == nullptr){
        return StatusType::FAILURE;
    }
    if((this->m_countryTree->m_root->findKey(countryId)->data->get_numsContestant() != 0)
       || (this->m_countryTree->m_root->findKey(countryId)->data->get_numsTeam() != 0)){
        return StatusType::FAILURE;
    }
    this->m_countryTree->m_root->deleteNode(this->m_countryTree->m_root, countryId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    return StatusType::FAILURE;
}

StatusType Olympics::remove_team(int teamId){
    return StatusType::FAILURE;
}

StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || contestantId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_contastantTree->m_root->findKey(contestantId) != nullptr){
        return StatusType::FAILURE;
    }
    if(this->m_countryTree->m_root->findKey(countryId) == nullptr){
        return StatusType::FAILURE;
    }
    Country* curr = this->m_countryTree->m_root->findKey(countryId)->data;
    Contestant* newContestant = new Contestant(contestantId, curr, sport,strength);
    if(newContestant == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<Contestant>* node = new Node<Contestant>(contestantId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->data = newContestant;
    this->m_contastantTree->m_root->insertNode(node);
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant(int contestantId){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (this->m_contastantTree->m_root->findKey(contestantId) == nullptr){
        return StatusType::FAILURE;
    }
    if (this->m_contastantTree->m_root->findKey(contestantId)->data->get_numTeam() > 0){
        return StatusType::FAILURE;
    }
    this->m_contastantTree->m_root->deleteNode(this->m_contastantTree->m_root, contestantId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
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
    if (this->m_contastantTree->m_root->findKey(contestantId) == nullptr){
        return StatusType::FAILURE;
    }
    return this->m_contastantTree->m_root->findKey(contestantId)->data->get_strength();
}

output_t<int> Olympics::get_medals(int countryId){
    if (countryId <= 0){
        return StatusType::FAILURE;
    }
    if (this->m_countryTree->m_root->findKey(countryId) == nullptr){
        return StatusType::FAILURE;
    }
    return this->m_countryTree->m_root->findKey(countryId)->data->get_medals();

}

output_t<int> Olympics::get_team_strength(int teamId){
    return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_TeamTree->m_root->findKey(teamId) == nullptr){
        return StatusType::FAILURE;
    }
    if(this->m_TeamTree->m_root->findKey(teamId)->data->m_numOfContestant < 3){
        return StatusType::FAILURE;
    }

    return 0;
}


