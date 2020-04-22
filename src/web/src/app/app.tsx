import * as React from "react";
import { useState } from "react";
import CssBaseline from "@material-ui/core/CssBaseline";
import { MainBar } from "./components/nav/main_bar";
import { MainDrawer } from "./components/nav/main_drawer";
import { BrowserRouter as Router, Route, Switch } from "react-router-dom";
import { Home } from "./pages/home";
import { Settings } from "./pages/settings";
import makeStyles from "@material-ui/core/styles/makeStyles";
import { Theme } from "@material-ui/core";

const useStyles = makeStyles((theme: Theme) => ({
  root: {
    margin: 24,
  }
}));

export const App = () => {
  const [isOpen, setIsOpen] = useState(false);
  const classes = useStyles();

  return (
    <Router>
      <>
        <CssBaseline/>

        <MainBar onMenuClicked={() => setIsOpen(true)}/>
        <MainDrawer isOpen={isOpen} onClose={() => setIsOpen(false)}/>

        <div className={classes.root}>
          <Switch>
            <Route path="/" exact={true} component={Home}/>
            <Route path="/settings" component={Settings}/>
          </Switch>
        </div>
      </>
    </Router>
  );
}
