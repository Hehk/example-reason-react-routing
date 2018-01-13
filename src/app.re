let str = ReasonReact.stringToElement;

type route =
  | Picture1
  | Picture2
  | Picture3
  | Picture4;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch url.path {
  | [] => Picture1
  | ["picture_2"] => Picture2
  | ["picture_3"] => Picture3
  | ["picture_4"] => Picture4
  | _ => Picture1
  };

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  reducer,
  initialState: () => {route: Picture1},
  subscriptions: (self) => [
    Sub(
      () => ReasonReact.Router.watchUrl((url) => self.send(ChangeRoute(url |> mapUrlToRoute))),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: (self) =>
    <div>
      <ul>
        <li> <Link href="picture_1"> (str("picture 1")) </Link> </li>
        <li> <Link href="picture_2"> (str("picture 2")) </Link> </li>
        <li> <Link href="picture_3"> (str("picture 3")) </Link> </li>
        <li> <Link href="picture_4"> (str("picture 4")) </Link> </li>
      </ul>
      <div>
        (
          switch self.state.route {
          | Picture1 =>
            <img
              src="https://cloud.githubusercontent.com/assets/1909539/25026859/84a5a4e8-205d-11e7-857b-777ce6909cfd.png"
              alt="picture 1"
            />
          | Picture2 => <img src="https://media.giphy.com/media/vKmHoLAQSKKhW/giphy.gif" alt="picture 2" />
          | Picture3 => <img src="https://media.giphy.com/media/WyeodYfrqvHCo/giphy.gif" alt="picture 3" />
          | Picture4 => <img src="https://media.giphy.com/media/nrXif9YExO9EI/giphy.gif" alt="picture 4" />
          }
        )
      </div>
    </div>
};
