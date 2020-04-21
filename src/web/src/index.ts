import {createElement} from "react";
import {render} from "react-dom";
import {App} from "./app/app";

render(
  createElement(App),
  document.getElementById("app"),
);
