""" Module providing main archive. """

from src.wpp import Whatsapp
from src.grafical import Grafical

def main():
    """ Main execution of all code. """

    wpp = Whatsapp()

    #frames = [wpp.ranking(),
    #wpp.repeated_message("dias")]

    # for frame, title in frames:
    #     graifico = Grafical(frame,title)
    #     x = frame.columns[0]
    #     for y in frame.columns[1:]:
    #         graifico.bar_plot(x, y)
    #         graifico.pie_plot(x, y)

    frame, title = wpp.week_chart()
    columns = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
    grafico = Grafical(frame,title)
    grafico.radar_chart(columns,frame.loc["AllUsers"][columns])

if __name__ == "__main__":
    main()
