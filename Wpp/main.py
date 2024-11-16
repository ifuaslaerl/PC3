""" Module providing main archive. """

from src.wpp import Whatsapp
from src.grafical import Grafical

def main():
    """ Main execution of all code. """

    wpp = Whatsapp()

    wpp.rename_user("Luís Rafael Sena", "Eu")
    wpp.rename_user("Mô 🤓❤️", "Amor")

    frame, title = wpp.word_count()

    frame.to_csv(f"{title}.csv")

if __name__ == "__main__":
    main()
