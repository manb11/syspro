class Card(object):
    RANKS = ["A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"]
    SUITS = ["c", "d", "h", "s"]

    def __init__(self, rank, suit, face_up=True):
        self.rank = rank
        self.suit = suit
        self.is_face_up = face_up

    def __str__(self):
        if self.is_face_up:
            rep = self.rank + self.suit
        else:
            rep = "XX"
        return rep

    def flip(self):
        self.is_face_up = not self.is_face_up


class Hand(object):
    """A hand of playing cards."""
    def __init__(self):
        self.cards = []

    def __str__(self):
        if self.cards:
            rep = ""
            for card in self.cards:
                rep += str(card) + "\t"
        else:
            rep = "<empty>"
        return rep

    def clear(self):
        self.cards = []

    def add(self, card):
        self.cards.append(card)

    def give(self, card, other_hand):
        self.cards.remove(card)
        other_hand.add(card)


class Deck(Hand):
    """A deck of playing cards."""
    def populate(self):
        for suit in Card.SUITS:
            for rank in Card.RANKS:
                self.add(Card(rank, suit))

    def shuffle(self):
        import random
        random.shuffle(self.cards)

    def deal(self, hands, per_hand=1):
        for rounds in range(per_hand):
            for hand in hands:
                if self.cards:
                    top_card = self.cards[0]
                    self.give(top_card, hand)
                else:
                    print("Out of cards!")


class Player(object):
    """A player for a game."""
    def __init__(self, name, score=0):
        self.name = name
        self.score = score

    def __str__(self):
        rep = self.name + ":\t" + str(self.score)
        return rep

    @staticmethod
    def ask_yes_no(question):
        """Ask a yes or no question."""
        response = None
        while response not in ("y", "n"):
            response = input(question).lower()
        return response

    @staticmethod
    def ask_number(question, low, high):
        """Ask for a number within a range."""
        response = None
        while response not in range(low, high):
            response = int(input(question))
        return response


class PositionnableCard(Card):
    ACE_VALUE = 1

    @property
    def value(self):
        if self.is_face_up:
            v = Card.RANKS.index(self.rank) + 1
            if v > 10:
                v = 10
            return v
        return 0


class BJ_Deck(Deck):
    """A Blackjack Deck."""
    def populate(self):
        for suit in PositionnableCard.SUITS:
            for rank in PositionnableCard.RANKS:
                self.add(PositionnableCard(rank, suit))


class BJ_Hand(Hand):
    """A Blackjack Hand."""
    def __init__(self, name):
        super(BJ_Hand, self).__init__()
        self.name = name

    def __str__(self):
        rep = self.name + ":\t" + super(BJ_Hand, self).__str__()
        if self.total:
            rep += "(" + str(self.total) + ")"
        return rep

    @property
    def total(self):
        for card in self.cards:
            if not card.value:
                return None
        t = 0
        contains_ace = False
        for card in self.cards:
            t += card.value
            if card.value == PositionnableCard.ACE_VALUE:
                contains_ace = True
        if contains_ace and t <= 11:
            t += 10
        return t

    def is_busted(self):
        return self.total > 21


class BJ_Player(BJ_Hand):
    def is_hitting(self):
        response = Player.ask_yes_no("\n" + self.name + ", do you want a hit? (Y/N): ")
        return response == "y"

    def bust(self):
        print(self.name, "busts.")
        self.lose()

    def lose(self):
        print(self.name, "loses.")

    def win(self):
        print(self.name, "wins.")

    def push(self):
        print(self.name, "pushes.")


class BJ_Dealer(BJ_Hand):
    """A Blackjack Dealer."""
    def is_hitting(self):
        return self.total < 17

    def bust(self):
        print(self.name, "busts.")

    def flip_first_card(self):
        first_card = self.cards[0]
        first_card.flip()


class BJ_Game(object):
    """A Blackjack Game."""
    def __init__(self, names):
        self.players = []
        for name in names:
            player = BJ_Player(name)
            self.players.append(player)
        self.dealer = BJ_Dealer("Dealer")
        self.deck = BJ_Deck()
        self.deck.populate()
        self.deck.shuffle()

    @property
    def still_playing(self):
        sp = []
        for player in self.players:
            if not player.is_busted():
                sp.append(player)
        return sp

    def __additional_cards(self, player):
        while not player.is_busted() and player.is_hitting():
            self.deck.deal([player])
            print(player)
            if player.is_busted():
                player.bust()

    def play(self):
        self.deck.deal(self.players + [self.dealer], per_hand=2)
        self.dealer.flip_first_card()
        for player in self.players:
            print(player)
        print(self.dealer)

        for player in self.players:
            self.__additional_cards(player)
        self.dealer.flip_first_card()  

        if not self.still_playing:
            print(self.dealer)
        else:
            print(self.dealer)
            self.__additional_cards(self.dealer)
            if self.dealer.is_busted():
                for player in self.still_playing:
                    player.win()
                
            else:
                for player in self.still_playing:
                    if player.total > self.dealer.total:
                        player.win()
                    elif player.total < self.dealer.total:
                        player.lose()
                    else:
                        player.push()

        for player in self.players:
            player.clear()
        self.dealer.clear()


    """class Chip():
    dollar = 100
    amount = 1

    betting = amount >= 1
    def money (Player):
        if Player.win():
            dollar = dollar + betting
        elif Player.lose():
            dolloar = dollar - betting
        else:
            print("=") """


    @staticmethod
    def main():
        print("\t\tWelcome to Blackjack!\n")

        names = []
        number = Player.ask_number("How many players? (1 - 7): ", low=1, high=8)
        for i in range(number):
            name = input("Enter player name: ")
            names.append(name)
        print()

        #betting = int(input(names, "How much will you bat($)? : "))

        game = BJ_Game(names)
        again = None
        while again != "n":
            game.play()
            again = Player.ask_yes_no("\nWant to play again?: ")


if __name__ == "__main__":
    BJ_Game.main()
    input("\n\nPress the enter key to exit.")
