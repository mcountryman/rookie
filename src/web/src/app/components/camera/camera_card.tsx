import * as React from "react";
import { Card } from "@material-ui/core";
import CardContent from "@material-ui/core/CardContent";
import CardHeader from "@material-ui/core/CardHeader";
import CardActions from "@material-ui/core/CardActions";
import IconButton from "@material-ui/core/IconButton";
import SaveIcon from "@material-ui/icons/Save";
import Grid from "@material-ui/core/Grid";
import { CameraDeviceId } from "./camera_device_id";
import { CameraProperties } from "./camera_properties";
import { useState } from "react";
import Collapse from "@material-ui/core/Collapse";
import Button from "@material-ui/core/Button";

export const CameraCard = () => {
  const [isCollapsed, setIsCollapsed] = useState(false);

  return (
    <>
      <Card>
        <CardHeader title="Camera"/>
        <CardContent>
          <Grid
            container
            spacing={3}
            direction="column">

            <CameraDeviceId
              addSaveHandler={handler => {}} />

            <Collapse in={isCollapsed}>
              <CameraProperties
                addSaveHandler={handler => {}}/>
            </Collapse>
          </Grid>
        </CardContent>
        <CardActions>
          <Button onClick={() => {}} >
            Save
          </Button>
          <Button onClick={() => setIsCollapsed(!isCollapsed)}>
            Properties
          </Button>
        </CardActions>
      </Card>
    </>
  );
};
