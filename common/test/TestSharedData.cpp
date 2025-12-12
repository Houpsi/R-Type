/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** TestSharedData
*/

//#include <gtest/gtest.h>
//#include "shared_data/SharedData.hpp" // Inclure le header de votre classe
//#include "packet_data/PacketData.hpp"
//using namespace server;
//
//// Création d'un fixture de test pour SharedData
//class SharedDataTest : public ::testing::Test {
//protected:
//    // Instance de la classe à tester
//    cmn::SharedData sharedData;
//    // Données de test pour PacketData (simples pour l'exemple)
//    cmn::packetData testPacket1 = {1, "Move", 0};
//    cmn::packetData testPacket2 = {2, "Shoot", 1};
//};
//
///**
// * @brief Tests pour les méthodes d'ajout et de récupération de la queue de réception.
// */
//TEST_F(SharedDataTest, ReceivedQueue_AddAndGetSinglePacket)
//{
//    // 1. Ajouter un paquet
//    sharedData.addReceivedPacket(testPacket1);
//
//    // 2. Récupérer et vérifier le paquet
//    auto retrieved = sharedData.getReceivedPacket();
//    ASSERT_TRUE(retrieved.has_value());
//    EXPECT_EQ(retrieved->commandId, 1);
//    EXPECT_EQ(retrieved->commandName, "Move");
//
//    // 3. Vérifier que la queue est maintenant vide
//    EXPECT_FALSE(sharedData.getReceivedPacket().has_value());
//}
//
//TEST_F(SharedDataTest, ReceivedQueue_FifoOrder)
//{
//    // 1. Ajouter deux paquets dans l'ordre
//    sharedData.addReceivedPacket(testPacket1);
//    sharedData.addReceivedPacket(testPacket2);
//
//    // 2. Récupérer le premier (doit être testPacket1)
//    auto first = sharedData.getReceivedPacket();
//    ASSERT_TRUE(first.has_value());
//    EXPECT_EQ(first->commandId, 1);
//
//    // 3. Récupérer le second (doit être testPacket2)
//    auto second = sharedData.getReceivedPacket();
//    ASSERT_TRUE(second.has_value());
//    EXPECT_EQ(second->commandId, 2);
//
//    // 4. Vérifier que la queue est vide
//    EXPECT_FALSE(sharedData.getReceivedPacket().has_value());
//}
//
//TEST_F(SharedDataTest, ReceivedQueue_GetFromEmptyQueue)
//{
//    // Tenter de récupérer d'une queue vide
//    EXPECT_FALSE(sharedData.getReceivedPacket().has_value());
//}
//
///**
// * @brief Tests pour les méthodes d'ajout et de récupération de la queue d'envoi.
// */
//TEST_F(SharedDataTest, SendQueue_AddAndGetSinglePacket)
//{
//    // 1. Ajouter un paquet
//    sharedData.addSendPacket(testPacket2);
//
//    // 2. Récupérer et vérifier le paquet
//    auto retrieved = sharedData.getSendPacket();
//    ASSERT_TRUE(retrieved.has_value());
//    EXPECT_EQ(retrieved->commandId, 2);
//
//    // 3. Vérifier que la queue est maintenant vide
//    EXPECT_FALSE(sharedData.getSendPacket().has_value());
//}
//
//TEST_F(SharedDataTest, SendQueue_GetFromEmptyQueue)
//{
//    // Tenter de récupérer d'une queue vide
//    EXPECT_FALSE(sharedData.getSendPacket().has_value());
//}
//
///**
// * @brief Tests pour la gestion des joueurs.
// */
//TEST_F(SharedDataTest, PlayerList_AddAndGetPlayer)
//{
//    int playerId = 42;
//    int port = 8080;
//    std::string ip = "127.0.0.1";
//
//    // 1. Ajouter un joueur
//    sharedData.addPlayer(playerId, port, ip);
//
//    // 2. Récupérer et vérifier le joueur
//    auto playerInfo = sharedData.getPlayer(playerId);
//    ASSERT_TRUE(playerInfo.has_value());
//    EXPECT_EQ(playerInfo->first, port);
//    EXPECT_EQ(playerInfo->second, ip);
//}
//
//TEST_F(SharedDataTest, PlayerList_GetNonExistingPlayer)
//{
//    // Tenter de récupérer un joueur non ajouté
//    EXPECT_FALSE(sharedData.getPlayer(999).has_value());
//}
//
//TEST_F(SharedDataTest, PlayerList_MultiplePlayers)
//{
//    // Ajouter deux joueurs
//    sharedData.addPlayer(1, 4000, "192.168.1.1");
//    sharedData.addPlayer(2, 4001, "192.168.1.2");
//
//    // Vérifier les deux
//    auto player1 = sharedData.getPlayer(1);
//    ASSERT_TRUE(player1.has_value());
//    EXPECT_EQ(player1->first, 4000);
//
//    auto player2 = sharedData.getPlayer(2);
//    ASSERT_TRUE(player2.has_value());
//    EXPECT_EQ(player2->second, "192.168.1.2");
//}

// NOTE: Le test de concurrence réel (Thread Safety) est plus complexe et
// nécessiterait la création de plusieurs threads GTest. Cependant, l'utilisation
// de `std::lock_guard` dans *toutes* les méthodes publiques garantit
// théoriquement la sécurité des threads.
// Un test de base pour la concurrence pourrait ressembler à ceci (mais est souvent
// laissé de côté dans les tests unitaires simples) :

/*
TEST_F(SharedDataTest, ConcurrencyTest)
{
    // Créer deux threads qui ajoutent simultanément des paquets
    auto concurrent_add = [&]() {
        for (int i = 0; i < 1000; ++i) {
            sharedData.addReceivedPacket({i, "Concurrent", 0});
        }
    };

    std::thread t1(concurrent_add);
    std::thread t2(concurrent_add);

    t1.join();
    t2.join();

    // Vérifier que 2000 paquets ont été ajoutés et peuvent être retirés
    int count = 0;
    while (sharedData.getReceivedPacket().has_value()) {
        count++;
    }
    EXPECT_EQ(count, 2000);
}
*/