from pathlib import Path

import pandas as pd
import plotly.graph_objects as go


ROOT = Path(__file__).resolve().parent.parent


def read_csv(filename: str) -> pd.DataFrame:
    data = pd.read_csv(ROOT / filename)
    data.columns = data.columns.str.strip()
    return data


def show_alphabet_time_plot(data: pd.DataFrame) -> None:
    fig = go.Figure()
    fig.add_trace(go.Scatter(
        x=data["Alphabet Size"],
        y=data["Used Time Algorithm 1"],
        mode="lines+markers",
        name="Algorithm 1",
    ))
    fig.add_trace(go.Scatter(
        x=data["Alphabet Size"],
        y=data["Used Time Algorithm 2"],
        mode="lines+markers",
        name="Algorithm 2",
    ))
    fig.update_layout(
        title="Сравнение времени выполнения по размеру алфавита",
        xaxis_title="Размер алфавита",
        yaxis_title="Время",
        template="simple_white",
    )
    fig.show()


def show_word_time_plot(data: pd.DataFrame) -> None:
    fig = go.Figure()
    fig.add_trace(go.Scatter(
        x=data["Word Size"],
        y=data["Used Time Algorithm 1"],
        mode="lines+markers",
        name="Algorithm 1",
    ))
    fig.add_trace(go.Scatter(
        x=data["Word Size"],
        y=data["Used Time Algorithm 2"],
        mode="lines+markers",
        name="Algorithm 2",
    ))
    fig.update_layout(
        title="Сравнение времени выполнения по размеру слова",
        xaxis_title="Размер слова",
        yaxis_title="Время",
        template="simple_white",
    )
    fig.show()


def show_operation_plots(data: pd.DataFrame) -> None:
    fig1 = go.Figure()
    fig1.add_trace(go.Scatter(
        x=data["Word Size"],
        y=data["Word Size"] * data["Word Size"] * 500 / 10,
        mode="lines+markers",
        name="Оценка O(n*m*l)",
    ))
    fig1.add_trace(go.Scatter(
        x=data["Word Size"],
        y=data["Used Operations Algorithm 1"],
        mode="lines+markers",
        name="Algorithm 1",
    ))
    fig1.update_layout(
        title="Оценка сложности наивного алгоритма",
        xaxis_title="Размер слова",
        yaxis_title="Количество операций",
        template="simple_white",
    )
    fig1.show()

    fig2 = go.Figure()
    fig2.add_trace(go.Scatter(
        x=data["Word Size"],
        y=(data["Word Size"] + data["Word Size"] / 10) * 500,
        mode="lines+markers",
        name="Оценка O(n*(m+l))",
    ))
    fig2.add_trace(go.Scatter(
        x=data["Word Size"],
        y=data["Used Operations Algorithm 2"],
        mode="lines+markers",
        name="Algorithm 2",
    ))
    fig2.update_layout(
        title="Оценка сложности Boyer–Moore",
        xaxis_title="Размер слова",
        yaxis_title="Количество операций",
        template="simple_white",
    )
    fig2.show()


def main() -> None:
    alphabet_data = read_csv("out1.csv")
    word_data = read_csv("out2.csv")

    show_alphabet_time_plot(alphabet_data)
    show_word_time_plot(word_data)
    show_operation_plots(word_data)


if __name__ == "__main__":
    main()
