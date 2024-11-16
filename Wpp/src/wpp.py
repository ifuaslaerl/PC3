""" Module containing whatsapp processing class. """

import re
import typing
from collections import Counter
import pandas as pd

class Whatsapp:
    """ Class used to process whatsapp chat. """

    def __init__(self, path="WppFolder/chat.txt"):
        self.path = path
        with open(path,encoding="UTF-8") as f:
            self.chat = f.read()
            line_format = \
                r'(\d{1,2}\/\d{1,2}\/\d{1,4}) (\d{1,2}:\d{1,2}) - (.+?): (.*)'
            pattern = re.compile(line_format)
            data = pattern.findall(self.chat)
            self.data = pd.DataFrame(data, columns=["Day", "Hour", "User", "Message"])

            self.data["Datetime"] = pd.to_datetime(self.data["Day"] + " " + self.data["Hour"],
                                                    format="%d/%m/%Y %H:%M")

            self.data.drop(columns=["Day", "Hour"], inplace=True)
            self.data = self.data[["Datetime", "User", "Message"]]

    def __len__(self) -> int:
        return len(self.data)

    def rename_user(self, user: str, new_name: str) -> None:
        """ Rename user to new_name. """
        self.data["User"] = self.data["User"].replace(user,new_name)

    def ranking(self) -> typing.Tuple[pd.DataFrame , str]:
        """ Gets the ranking of who sends the maximum amount of messages. """
        message_frame = self.data["User"].value_counts().reset_index()
        message_frame.columns = ["User", "MessageCount"]

        char_frame = self.data.groupby("User")["Message"].\
            apply(lambda x: x.str.len().sum()).reset_index()

        char_frame.columns = ["User", "TotalCharacters"]

        ranking = pd.merge(message_frame, char_frame)

        ranking = ranking[["User", "MessageCount", "TotalCharacters"]]

        return ranking, "Ranking"

    def emoji_count(self) -> typing.Tuple[pd.DataFrame , str]:
        """ Get frequency of all emojis. """

        emoji_pattern = re.compile(
            "[" 
            "\U0001F600-\U0001F64F"  # Emojis de rosto
            "\U0001F300-\U0001F5FF"  # Símbolos e pictogramas
            "\U0001F680-\U0001F6FF"  # Transporte e mapas
            "\U0001F1E0-\U0001F1FF"  # Bandeiras
            "\U00002700-\U000027BF"  # Diversos símbolos adicionais
            "\U000024C2-\U0001F251"  # Símbolos diversos
            "]+"
        )
        all_emojis = []

        for message in self.data["Message"]:
            found_emojis = emoji_pattern.findall(message)

            for emoji in found_emojis:
                all_emojis.extend(list(emoji))

        emoji_counts = Counter(all_emojis)

        emoji_df = pd.DataFrame(emoji_counts.items(), columns=["Emoji", "Count"])
        emoji_df.sort_values(by="Count", ascending=False, inplace=True)

        emoji_df.reset_index(drop=True, inplace=True)

        return emoji_df, "Emojis"

    def week_chart(self) -> typing.Tuple[pd.DataFrame , str]:
        """ Get amount of messages in days of week. """

        frame = pd.DataFrame()
        frame["User"] = self.data["User"]
        frame["WeekDay"] = self.data["Datetime"].dt.strftime('%A')

        frame = frame.groupby(['User', 'WeekDay']).size().unstack(fill_value=0)

        frame.columns.name = None
        frame.reset_index(inplace=True)

        frame = frame[["User", "Sunday", "Monday", "Tuesday",\
                        "Wednesday", "Thursday", "Friday", "Saturday"]]

        frame.loc[len(frame)] = frame.sum()
        frame["User"][2] = "AllUsers"

        return frame , "WeekFrequency"

    def repeated_message(self, find: str) -> typing.Tuple[pd.DataFrame , str]:
        """ Get amount of repetition os string in messages. """

        frame = pd.DataFrame()
        frame["Frequency"] = self.data["Message"].str.count(find)
        frame["User"] = self.data["User"]

        frame = frame.groupby("User")["Frequency"].sum().reset_index()

        return frame , f"Frequency of {find}"

    def word_count(self)-> typing.Tuple[pd.DataFrame , str]:
        """ Cria um DataFrame que representa a quantidade de vezes que
            cada usuário digitou cada palavra.
        """
        contador_usuarios = {}

        for usuario, mensagens in self.data.groupby("User")["Message"]:
            texto = ' '.join(mensagens).lower()
            palavras_contadas = Counter(texto.split())
            contador_usuarios[usuario] = palavras_contadas

        frame = pd.DataFrame.from_dict(contador_usuarios, orient='index').\
                fillna(0).astype(int)

        frame = frame.loc[frame.sum(axis=1).sort_values(ascending=False).index]

        frame = frame[frame.sum(axis=0).sort_values(ascending=False).index]

        return frame.T, "WordFrequency"

def main():
    """ Debugging function. """

    wpp = Whatsapp()

    wpp.rename_user("Luís Rafael Sena","Eu")
    wpp.rename_user("Mô 🤓❤️","Amor")

    print(wpp.ranking()[0].head())
    print(wpp.emoji_count()[0].head())
    print(wpp.week_chart()[0].head())
    print(wpp.repeated_message("amo")[0])
    print(wpp.word_count()[0])

if __name__ == "__main__":
    main()
